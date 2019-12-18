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
struct dce_clk_mgr {int dummy; } ;
struct clk_mgr {int dummy; } ;

/* Variables and functions */
 struct dce_clk_mgr* TO_DCE_CLK_MGR (struct clk_mgr*) ; 
 int /*<<< orphan*/  kfree (struct dce_clk_mgr*) ; 

void dce_clk_mgr_destroy(struct clk_mgr **clk_mgr)
{
	struct dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(*clk_mgr);

	kfree(clk_mgr_dce);
	*clk_mgr = NULL;
}