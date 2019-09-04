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
struct videomode {unsigned long pixelclock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc_channel; } ;
struct dpi_data {TYPE_1__ output; scalar_t__ pll; struct videomode vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSWARN (char*,unsigned long,unsigned long) ; 
 int dpi_set_dispc_clk (struct dpi_data*,unsigned long,unsigned long*,int*,int*) ; 
 int dpi_set_pll_clk (struct dpi_data*,int /*<<< orphan*/ ,unsigned long,unsigned long*,int*,int*) ; 
 int /*<<< orphan*/  dss_mgr_set_timings (TYPE_1__*,struct videomode*) ; 

__attribute__((used)) static int dpi_set_mode(struct dpi_data *dpi)
{
	struct videomode *vm = &dpi->vm;
	int lck_div = 0, pck_div = 0;
	unsigned long fck = 0;
	unsigned long pck;
	int r = 0;

	if (dpi->pll)
		r = dpi_set_pll_clk(dpi, dpi->output.dispc_channel,
				    vm->pixelclock, &fck, &lck_div, &pck_div);
	else
		r = dpi_set_dispc_clk(dpi, vm->pixelclock, &fck,
				&lck_div, &pck_div);
	if (r)
		return r;

	pck = fck / lck_div / pck_div;

	if (pck != vm->pixelclock) {
		DSSWARN("Could not find exact pixel clock. Requested %lu Hz, got %lu Hz\n",
			vm->pixelclock, pck);

		vm->pixelclock = pck;
	}

	dss_mgr_set_timings(&dpi->output, vm);

	return 0;
}