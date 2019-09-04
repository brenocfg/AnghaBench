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
struct dss_pll_clock_info {int* mX; int clkdco; int* clkout; } ;
struct dsi_data {TYPE_1__* data; } ;
struct TYPE_2__ {unsigned long max_fck_freq; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned long) ; 
 size_t HSDIV_DSI ; 

__attribute__((used)) static void dsi_pll_calc_dsi_fck(struct dsi_data *dsi,
				 struct dss_pll_clock_info *cinfo)
{
	unsigned long max_dsi_fck;

	max_dsi_fck = dsi->data->max_fck_freq;

	cinfo->mX[HSDIV_DSI] = DIV_ROUND_UP(cinfo->clkdco, max_dsi_fck);
	cinfo->clkout[HSDIV_DSI] = cinfo->clkdco / cinfo->mX[HSDIV_DSI];
}