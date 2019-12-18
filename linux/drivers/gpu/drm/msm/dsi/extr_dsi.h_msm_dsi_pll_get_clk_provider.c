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
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int msm_dsi_pll_get_clk_provider(struct msm_dsi_pll *pll,
	struct clk **byte_clk_provider, struct clk **pixel_clk_provider)
{
	return -ENODEV;
}