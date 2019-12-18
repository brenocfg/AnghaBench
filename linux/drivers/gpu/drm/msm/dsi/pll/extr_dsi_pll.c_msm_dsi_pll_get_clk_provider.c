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
struct msm_dsi_pll {int (* get_provider ) (struct msm_dsi_pll*,struct clk**,struct clk**) ;} ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct msm_dsi_pll*,struct clk**,struct clk**) ; 

int msm_dsi_pll_get_clk_provider(struct msm_dsi_pll *pll,
	struct clk **byte_clk_provider, struct clk **pixel_clk_provider)
{
	if (pll->get_provider)
		return pll->get_provider(pll,
					byte_clk_provider,
					pixel_clk_provider);

	return -EINVAL;
}