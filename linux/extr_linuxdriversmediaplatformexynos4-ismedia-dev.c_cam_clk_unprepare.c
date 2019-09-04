#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct cam_clk {TYPE_1__* fmd; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pmf; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 struct cam_clk* to_cam_clk (struct clk_hw*) ; 

__attribute__((used)) static void cam_clk_unprepare(struct clk_hw *hw)
{
	struct cam_clk *camclk = to_cam_clk(hw);

	if (camclk->fmd->pmf == NULL)
		return;

	pm_runtime_put_sync(camclk->fmd->pmf);
}