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
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct dpi_data {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dpi_init_pll (struct dpi_data*) ; 
 int dpi_init_regulator (struct dpi_data*) ; 
 int dss_mgr_connect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 int /*<<< orphan*/  dss_mgr_disconnect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 int omapdss_output_set_device (struct omap_dss_device*,struct omap_dss_device*) ; 

__attribute__((used)) static int dpi_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	int r;

	r = dpi_init_regulator(dpi);
	if (r)
		return r;

	dpi_init_pll(dpi);

	r = dss_mgr_connect(&dpi->output, dssdev);
	if (r)
		return r;

	r = omapdss_output_set_device(dssdev, dst);
	if (r) {
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(&dpi->output, dssdev);
		return r;
	}

	return 0;
}