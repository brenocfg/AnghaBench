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
struct dss_pll {int dummy; } ;
struct dpi_data {struct dss_pll* pll; int /*<<< orphan*/  clk_src; int /*<<< orphan*/  dss; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSWARN (char*) ; 
 int /*<<< orphan*/  dpi_get_clk_src (struct dpi_data*) ; 
 scalar_t__ dpi_verify_pll (struct dss_pll*) ; 
 struct dss_pll* dss_pll_find_by_src (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpi_init_pll(struct dpi_data *dpi)
{
	struct dss_pll *pll;

	if (dpi->pll)
		return;

	dpi->clk_src = dpi_get_clk_src(dpi);

	pll = dss_pll_find_by_src(dpi->dss, dpi->clk_src);
	if (!pll)
		return;

	if (dpi_verify_pll(pll)) {
		DSSWARN("PLL not operational\n");
		return;
	}

	dpi->pll = pll;
}