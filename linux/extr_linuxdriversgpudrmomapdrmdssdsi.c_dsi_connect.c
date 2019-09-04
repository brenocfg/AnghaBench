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
struct dsi_data {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int dsi_regulator_init (struct dsi_data*) ; 
 int dss_mgr_connect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 int /*<<< orphan*/  dss_mgr_disconnect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 int omapdss_output_set_device (struct omap_dss_device*,struct omap_dss_device*) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dsi_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);
	int r;

	r = dsi_regulator_init(dsi);
	if (r)
		return r;

	r = dss_mgr_connect(&dsi->output, dssdev);
	if (r)
		return r;

	r = omapdss_output_set_device(dssdev, dst);
	if (r) {
		DSSERR("failed to connect output to new device: %s\n",
				dssdev->name);
		dss_mgr_disconnect(&dsi->output, dssdev);
		return r;
	}

	return 0;
}