#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ofdpa_port {TYPE_1__* dev; TYPE_2__* bridge_dev; int /*<<< orphan*/  internal_vlan_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  OFDPA_UNTAGGED_VID ; 
 int ofdpa_port_fwd_enable (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_port_internal_vlan_id_get (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_port_internal_vlan_id_put (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int ofdpa_port_vlan_add (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofdpa_port_vlan_del (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_bridge_leave(struct ofdpa_port *ofdpa_port)
{
	int err;

	err = ofdpa_port_vlan_del(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	if (err)
		return err;

	ofdpa_port_internal_vlan_id_put(ofdpa_port,
					ofdpa_port->bridge_dev->ifindex);
	ofdpa_port->internal_vlan_id =
		ofdpa_port_internal_vlan_id_get(ofdpa_port,
						ofdpa_port->dev->ifindex);

	ofdpa_port->bridge_dev = NULL;

	err = ofdpa_port_vlan_add(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	if (err)
		return err;

	if (ofdpa_port->dev->flags & IFF_UP)
		err = ofdpa_port_fwd_enable(ofdpa_port, 0);

	return err;
}