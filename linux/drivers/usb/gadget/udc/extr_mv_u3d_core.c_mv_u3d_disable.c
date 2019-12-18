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
struct mv_usb_platform_data {int /*<<< orphan*/  (* phy_deinit ) (int /*<<< orphan*/ ) ;} ;
struct mv_u3d {scalar_t__ active; int /*<<< orphan*/  clk; int /*<<< orphan*/  phy_regs; int /*<<< orphan*/  dev; scalar_t__ clock_gating; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct mv_usb_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_u3d_disable(struct mv_u3d *u3d)
{
	struct mv_usb_platform_data *pdata = dev_get_platdata(u3d->dev);
	if (u3d->clock_gating && u3d->active) {
		dev_dbg(u3d->dev, "disable u3d\n");
		if (pdata->phy_deinit)
			pdata->phy_deinit(u3d->phy_regs);
		clk_disable(u3d->clk);
		u3d->active = 0;
	}
}