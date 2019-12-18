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
struct TYPE_2__ {int /*<<< orphan*/  dispc_channel; } ;
struct dpi_data {int /*<<< orphan*/  pixelclock; TYPE_1__ output; scalar_t__ pll; } ;

/* Variables and functions */
 int dpi_set_dispc_clk (struct dpi_data*,int /*<<< orphan*/ ,unsigned long*,int*,int*) ; 
 int dpi_set_pll_clk (struct dpi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,int*,int*) ; 

__attribute__((used)) static int dpi_set_mode(struct dpi_data *dpi)
{
	int lck_div = 0, pck_div = 0;
	unsigned long fck = 0;
	int r = 0;

	if (dpi->pll)
		r = dpi_set_pll_clk(dpi, dpi->output.dispc_channel,
				    dpi->pixelclock, &fck, &lck_div, &pck_div);
	else
		r = dpi_set_dispc_clk(dpi, dpi->pixelclock, &fck,
				&lck_div, &pck_div);
	if (r)
		return r;

	return 0;
}