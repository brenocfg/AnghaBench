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
struct msm_dsi_pll {int dummy; } ;
struct dsi_pll_28nm {int /*<<< orphan*/  num_clks; int /*<<< orphan*/  clks; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_dsi_pll_helper_unregister_clks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsi_pll_28nm* to_pll_28nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static void dsi_pll_28nm_destroy(struct msm_dsi_pll *pll)
{
	struct dsi_pll_28nm *pll_28nm = to_pll_28nm(pll);

	msm_dsi_pll_helper_unregister_clks(pll_28nm->pdev,
					pll_28nm->clks, pll_28nm->num_clks);
}