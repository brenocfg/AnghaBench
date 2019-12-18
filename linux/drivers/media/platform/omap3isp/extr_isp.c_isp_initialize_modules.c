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
struct isp_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap3isp_ccdc_cleanup (struct isp_device*) ; 
 int omap3isp_ccdc_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_ccp2_cleanup (struct isp_device*) ; 
 int omap3isp_ccp2_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_csi2_cleanup (struct isp_device*) ; 
 int omap3isp_csi2_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_csiphy_cleanup (struct isp_device*) ; 
 int omap3isp_csiphy_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_h3a_aewb_cleanup (struct isp_device*) ; 
 int omap3isp_h3a_aewb_init (struct isp_device*) ; 
 int omap3isp_h3a_af_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_hist_cleanup (struct isp_device*) ; 
 int omap3isp_hist_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_preview_cleanup (struct isp_device*) ; 
 int omap3isp_preview_init (struct isp_device*) ; 
 int /*<<< orphan*/  omap3isp_resizer_cleanup (struct isp_device*) ; 
 int omap3isp_resizer_init (struct isp_device*) ; 

__attribute__((used)) static int isp_initialize_modules(struct isp_device *isp)
{
	int ret;

	ret = omap3isp_csiphy_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "CSI PHY initialization failed\n");
		return ret;
	}

	ret = omap3isp_csi2_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "CSI2 initialization failed\n");
		goto error_csi2;
	}

	ret = omap3isp_ccp2_init(isp);
	if (ret < 0) {
		if (ret != -EPROBE_DEFER)
			dev_err(isp->dev, "CCP2 initialization failed\n");
		goto error_ccp2;
	}

	ret = omap3isp_ccdc_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "CCDC initialization failed\n");
		goto error_ccdc;
	}

	ret = omap3isp_preview_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "Preview initialization failed\n");
		goto error_preview;
	}

	ret = omap3isp_resizer_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "Resizer initialization failed\n");
		goto error_resizer;
	}

	ret = omap3isp_hist_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "Histogram initialization failed\n");
		goto error_hist;
	}

	ret = omap3isp_h3a_aewb_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "H3A AEWB initialization failed\n");
		goto error_h3a_aewb;
	}

	ret = omap3isp_h3a_af_init(isp);
	if (ret < 0) {
		dev_err(isp->dev, "H3A AF initialization failed\n");
		goto error_h3a_af;
	}

	return 0;

error_h3a_af:
	omap3isp_h3a_aewb_cleanup(isp);
error_h3a_aewb:
	omap3isp_hist_cleanup(isp);
error_hist:
	omap3isp_resizer_cleanup(isp);
error_resizer:
	omap3isp_preview_cleanup(isp);
error_preview:
	omap3isp_ccdc_cleanup(isp);
error_ccdc:
	omap3isp_ccp2_cleanup(isp);
error_ccp2:
	omap3isp_csi2_cleanup(isp);
error_csi2:
	omap3isp_csiphy_cleanup(isp);

	return ret;
}