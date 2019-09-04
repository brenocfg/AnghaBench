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
struct dss_pll_clock_info {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  pll; struct dss_pll_clock_info user_dsi_cinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int dss_pll_set_config (int /*<<< orphan*/ *,struct dss_pll_clock_info*) ; 

__attribute__((used)) static int dsi_configure_dsi_clocks(struct dsi_data *dsi)
{
	struct dss_pll_clock_info cinfo;
	int r;

	cinfo = dsi->user_dsi_cinfo;

	r = dss_pll_set_config(&dsi->pll, &cinfo);
	if (r) {
		DSSERR("Failed to set dsi clocks\n");
		return r;
	}

	return 0;
}