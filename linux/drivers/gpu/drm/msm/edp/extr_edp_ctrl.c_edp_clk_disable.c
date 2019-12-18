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
typedef  int u32 ;
struct edp_ctrl {int /*<<< orphan*/  ahb_clk; int /*<<< orphan*/  aux_clk; int /*<<< orphan*/  link_clk; int /*<<< orphan*/  pixel_clk; int /*<<< orphan*/  mdp_core_clk; } ;

/* Variables and functions */
 int EDP_CLK_MASK_AHB ; 
 int EDP_CLK_MASK_AUX ; 
 int EDP_CLK_MASK_LINK ; 
 int EDP_CLK_MASK_MDP_CORE ; 
 int EDP_CLK_MASK_PIXEL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_clk_disable(struct edp_ctrl *ctrl, u32 clk_mask)
{
	if (clk_mask & EDP_CLK_MASK_MDP_CORE)
		clk_disable_unprepare(ctrl->mdp_core_clk);
	if (clk_mask & EDP_CLK_MASK_PIXEL)
		clk_disable_unprepare(ctrl->pixel_clk);
	if (clk_mask & EDP_CLK_MASK_LINK)
		clk_disable_unprepare(ctrl->link_clk);
	if (clk_mask & EDP_CLK_MASK_AUX)
		clk_disable_unprepare(ctrl->aux_clk);
	if (clk_mask & EDP_CLK_MASK_AHB)
		clk_disable_unprepare(ctrl->ahb_clk);
}