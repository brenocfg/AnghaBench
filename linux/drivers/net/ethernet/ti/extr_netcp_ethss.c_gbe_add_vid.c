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
struct gbe_priv {scalar_t__ ale_ports; int /*<<< orphan*/  ale; } ;
struct gbe_intf {int /*<<< orphan*/  active_vlans; struct gbe_priv* gbe_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBE_MASK_NO_PORTS ; 
 int /*<<< orphan*/  GBE_PORT_MASK (scalar_t__) ; 
 int /*<<< orphan*/  cpsw_ale_add_vlan (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbe_add_vid(void *intf_priv, int vid)
{
	struct gbe_intf *gbe_intf = intf_priv;
	struct gbe_priv *gbe_dev = gbe_intf->gbe_dev;

	set_bit(vid, gbe_intf->active_vlans);

	cpsw_ale_add_vlan(gbe_dev->ale, vid,
			  GBE_PORT_MASK(gbe_dev->ale_ports),
			  GBE_MASK_NO_PORTS,
			  GBE_PORT_MASK(gbe_dev->ale_ports),
			  GBE_PORT_MASK(gbe_dev->ale_ports - 1));

	return 0;
}