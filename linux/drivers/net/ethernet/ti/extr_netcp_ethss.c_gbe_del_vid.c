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
struct gbe_priv {int /*<<< orphan*/  ale; } ;
struct gbe_intf {int /*<<< orphan*/  active_vlans; struct gbe_priv* gbe_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_del_vlan (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbe_del_vid(void *intf_priv, int vid)
{
	struct gbe_intf *gbe_intf = intf_priv;
	struct gbe_priv *gbe_dev = gbe_intf->gbe_dev;

	cpsw_ale_del_vlan(gbe_dev->ale, vid, 0);
	clear_bit(vid, gbe_intf->active_vlans);
	return 0;
}