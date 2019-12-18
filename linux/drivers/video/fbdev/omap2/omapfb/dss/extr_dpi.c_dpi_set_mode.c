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
struct omap_video_timings {unsigned long pixelclock; } ;
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct omap_dss_device {struct omap_overlay_manager* manager; } ;
struct dpi_data {scalar_t__ pll; struct omap_video_timings timings; struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSWARN (char*,unsigned long,unsigned long) ; 
 int dpi_set_dispc_clk (struct dpi_data*,unsigned long,unsigned long*,int*,int*) ; 
 int dpi_set_dsi_clk (struct dpi_data*,int /*<<< orphan*/ ,unsigned long,unsigned long*,int*,int*) ; 
 int /*<<< orphan*/  dss_mgr_set_timings (struct omap_overlay_manager*,struct omap_video_timings*) ; 

__attribute__((used)) static int dpi_set_mode(struct dpi_data *dpi)
{
	struct omap_dss_device *out = &dpi->output;
	struct omap_overlay_manager *mgr = out->manager;
	struct omap_video_timings *t = &dpi->timings;
	int lck_div = 0, pck_div = 0;
	unsigned long fck = 0;
	unsigned long pck;
	int r = 0;

	if (dpi->pll)
		r = dpi_set_dsi_clk(dpi, mgr->id, t->pixelclock, &fck,
				&lck_div, &pck_div);
	else
		r = dpi_set_dispc_clk(dpi, t->pixelclock, &fck,
				&lck_div, &pck_div);
	if (r)
		return r;

	pck = fck / lck_div / pck_div;

	if (pck != t->pixelclock) {
		DSSWARN("Could not find exact pixel clock. Requested %d Hz, got %lu Hz\n",
			t->pixelclock, pck);

		t->pixelclock = pck;
	}

	dss_mgr_set_timings(mgr, t);

	return 0;
}