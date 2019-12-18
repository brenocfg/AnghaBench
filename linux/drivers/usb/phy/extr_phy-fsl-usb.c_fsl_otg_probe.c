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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FSL_OTG_MAJOR ; 
 int /*<<< orphan*/  FSL_OTG_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int fsl_otg_conf (struct platform_device*) ; 
 int /*<<< orphan*/  otg_fops ; 
 int register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_otg_start (struct platform_device*) ; 

__attribute__((used)) static int fsl_otg_probe(struct platform_device *pdev)
{
	int ret;

	if (!dev_get_platdata(&pdev->dev))
		return -ENODEV;

	/* configure the OTG */
	ret = fsl_otg_conf(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't configure OTG module\n");
		return ret;
	}

	/* start OTG */
	ret = usb_otg_start(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Can't init FSL OTG device\n");
		return ret;
	}

	ret = register_chrdev(FSL_OTG_MAJOR, FSL_OTG_NAME, &otg_fops);
	if (ret) {
		dev_err(&pdev->dev, "unable to register FSL OTG device\n");
		return ret;
	}

	return ret;
}