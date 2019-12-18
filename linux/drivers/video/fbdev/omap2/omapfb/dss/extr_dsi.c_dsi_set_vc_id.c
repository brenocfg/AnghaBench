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
struct platform_device {int dummy; } ;
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct dsi_data {TYPE_1__* vc; } ;
struct TYPE_2__ {int vc_id; struct omap_dss_device* dssdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EINVAL ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 

__attribute__((used)) static int dsi_set_vc_id(struct omap_dss_device *dssdev, int channel, int vc_id)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	if (vc_id < 0 || vc_id > 3) {
		DSSERR("VC ID out of range\n");
		return -EINVAL;
	}

	if (channel < 0 || channel > 3) {
		DSSERR("Virtual Channel out of range\n");
		return -EINVAL;
	}

	if (dsi->vc[channel].dssdev != dssdev) {
		DSSERR("Virtual Channel not allocated to display %s\n",
			dssdev->name);
		return -EINVAL;
	}

	dsi->vc[channel].vc_id = vc_id;

	return 0;
}