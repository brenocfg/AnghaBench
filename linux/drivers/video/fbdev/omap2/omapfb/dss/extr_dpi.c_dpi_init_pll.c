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
struct dss_pll {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc_channel; } ;
struct dpi_data {struct dss_pll* pll; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSWARN (char*) ; 
 scalar_t__ OMAPDSS_VER_DRA7xx ; 
 struct dss_pll* dpi_get_pll (int /*<<< orphan*/ ) ; 
 scalar_t__ dpi_verify_dsi_pll (struct dss_pll*) ; 
 int /*<<< orphan*/  dss_ctrl_pll_set_control_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omapdss_get_version () ; 

__attribute__((used)) static void dpi_init_pll(struct dpi_data *dpi)
{
	struct dss_pll *pll;

	if (dpi->pll)
		return;

	pll = dpi_get_pll(dpi->output.dispc_channel);
	if (!pll)
		return;

	/* On DRA7 we need to set a mux to use the PLL */
	if (omapdss_get_version() == OMAPDSS_VER_DRA7xx)
		dss_ctrl_pll_set_control_mux(pll->id, dpi->output.dispc_channel);

	if (dpi_verify_dsi_pll(pll)) {
		DSSWARN("DSI PLL not operational\n");
		return;
	}

	dpi->pll = pll;
}