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
struct platform_device {int /*<<< orphan*/  dev; TYPE_1__* id_entry; } ;
struct fsl_usb2_platform_data {scalar_t__ phy_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FSL_USB2_PHY_ULPI ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct fsl_usb2_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * mxc_ahb_clk ; 
 int /*<<< orphan*/ * mxc_ipg_clk ; 
 int /*<<< orphan*/ * mxc_per_clk ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int fsl_udc_clk_init(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata;
	unsigned long freq;
	int ret;

	pdata = dev_get_platdata(&pdev->dev);

	mxc_ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(mxc_ipg_clk)) {
		dev_err(&pdev->dev, "clk_get(\"ipg\") failed\n");
		return PTR_ERR(mxc_ipg_clk);
	}

	mxc_ahb_clk = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(mxc_ahb_clk)) {
		dev_err(&pdev->dev, "clk_get(\"ahb\") failed\n");
		return PTR_ERR(mxc_ahb_clk);
	}

	mxc_per_clk = devm_clk_get(&pdev->dev, "per");
	if (IS_ERR(mxc_per_clk)) {
		dev_err(&pdev->dev, "clk_get(\"per\") failed\n");
		return PTR_ERR(mxc_per_clk);
	}

	clk_prepare_enable(mxc_ipg_clk);
	clk_prepare_enable(mxc_ahb_clk);
	clk_prepare_enable(mxc_per_clk);

	/* make sure USB_CLK is running at 60 MHz +/- 1000 Hz */
	if (!strcmp(pdev->id_entry->name, "imx-udc-mx27")) {
		freq = clk_get_rate(mxc_per_clk);
		if (pdata->phy_mode != FSL_USB2_PHY_ULPI &&
		    (freq < 59999000 || freq > 60001000)) {
			dev_err(&pdev->dev, "USB_CLK=%lu, should be 60MHz\n", freq);
			ret = -EINVAL;
			goto eclkrate;
		}
	}

	return 0;

eclkrate:
	clk_disable_unprepare(mxc_ipg_clk);
	clk_disable_unprepare(mxc_ahb_clk);
	clk_disable_unprepare(mxc_per_clk);
	mxc_per_clk = NULL;
	return ret;
}