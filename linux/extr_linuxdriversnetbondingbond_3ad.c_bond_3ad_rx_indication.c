#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct slave {TYPE_2__* bond; TYPE_1__* dev; } ;
struct port {int /*<<< orphan*/  actor_port_number; int /*<<< orphan*/  slave; } ;
struct lacpdu {int subtype; } ;
struct bond_marker {int /*<<< orphan*/  tlv_type; } ;
struct TYPE_8__ {struct port port; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_3__* dev; int /*<<< orphan*/  mode_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  AD_MARKER_INFORMATION_SUBTYPE 131 
#define  AD_MARKER_RESPONSE_SUBTYPE 130 
#define  AD_TYPE_LACPDU 129 
#define  AD_TYPE_MARKER 128 
 int RX_HANDLER_ANOTHER ; 
 int RX_HANDLER_CONSUMED ; 
 TYPE_4__* SLAVE_AD_INFO (struct slave*) ; 
 int /*<<< orphan*/  ad_marker_info_received (struct bond_marker*,struct port*) ; 
 int /*<<< orphan*/  ad_marker_response_received (struct bond_marker*,struct port*) ; 
 int /*<<< orphan*/  ad_rx_machine (struct lacpdu*,struct port*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bond_3ad_rx_indication(struct lacpdu *lacpdu, struct slave *slave,
				  u16 length)
{
	struct port *port;
	int ret = RX_HANDLER_ANOTHER;

	if (length >= sizeof(struct lacpdu)) {

		port = &(SLAVE_AD_INFO(slave)->port);

		if (!port->slave) {
			net_warn_ratelimited("%s: Warning: port of slave %s is uninitialized\n",
					     slave->dev->name, slave->bond->dev->name);
			return ret;
		}

		switch (lacpdu->subtype) {
		case AD_TYPE_LACPDU:
			ret = RX_HANDLER_CONSUMED;
			netdev_dbg(slave->bond->dev,
				   "Received LACPDU on port %d slave %s\n",
				   port->actor_port_number,
				   slave->dev->name);
			/* Protect against concurrent state machines */
			spin_lock(&slave->bond->mode_lock);
			ad_rx_machine(lacpdu, port);
			spin_unlock(&slave->bond->mode_lock);
			break;

		case AD_TYPE_MARKER:
			ret = RX_HANDLER_CONSUMED;
			/* No need to convert fields to Little Endian since we
			 * don't use the marker's fields.
			 */

			switch (((struct bond_marker *)lacpdu)->tlv_type) {
			case AD_MARKER_INFORMATION_SUBTYPE:
				netdev_dbg(slave->bond->dev, "Received Marker Information on port %d\n",
					   port->actor_port_number);
				ad_marker_info_received((struct bond_marker *)lacpdu, port);
				break;

			case AD_MARKER_RESPONSE_SUBTYPE:
				netdev_dbg(slave->bond->dev, "Received Marker Response on port %d\n",
					   port->actor_port_number);
				ad_marker_response_received((struct bond_marker *)lacpdu, port);
				break;

			default:
				netdev_dbg(slave->bond->dev, "Received an unknown Marker subtype on slot %d\n",
					   port->actor_port_number);
			}
		}
	}
	return ret;
}