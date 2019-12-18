#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int ofdpa_port_fdb (struct ofdpa_port*,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_port_is_bridged (struct ofdpa_port*) ; 
 int /*<<< orphan*/  ofdpa_port_vid_to_vlan (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofdpa_port_obj_fdb_add(struct rocker_port *rocker_port,
				  u16 vid, const unsigned char *addr)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;
	__be16 vlan_id = ofdpa_port_vid_to_vlan(ofdpa_port, vid, NULL);

	if (!ofdpa_port_is_bridged(ofdpa_port))
		return -EINVAL;

	return ofdpa_port_fdb(ofdpa_port, addr, vlan_id, 0);
}