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
struct of_device_id {int /*<<< orphan*/  data; } ;
struct gpmi_nand_data {int /*<<< orphan*/ * dev; struct platform_device* pdev; int /*<<< orphan*/  devdata; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __gpmi_enable_clk (struct gpmi_nand_data*,int) ; 
 int acquire_resources (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct gpmi_nand_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gpmi_init (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_nand_id_table ; 
 int gpmi_nand_init (struct gpmi_nand_data*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resources (struct gpmi_nand_data*) ; 

__attribute__((used)) static int gpmi_nand_probe(struct platform_device *pdev)
{
	struct gpmi_nand_data *this;
	const struct of_device_id *of_id;
	int ret;

	this = devm_kzalloc(&pdev->dev, sizeof(*this), GFP_KERNEL);
	if (!this)
		return -ENOMEM;

	of_id = of_match_device(gpmi_nand_id_table, &pdev->dev);
	if (of_id) {
		this->devdata = of_id->data;
	} else {
		dev_err(&pdev->dev, "Failed to find the right device id.\n");
		return -ENODEV;
	}

	platform_set_drvdata(pdev, this);
	this->pdev  = pdev;
	this->dev   = &pdev->dev;

	ret = acquire_resources(this);
	if (ret)
		goto exit_acquire_resources;

	ret = __gpmi_enable_clk(this, true);
	if (ret)
		goto exit_nfc_init;

	pm_runtime_set_autosuspend_delay(&pdev->dev, 500);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	ret = gpmi_init(this);
	if (ret)
		goto exit_nfc_init;

	ret = gpmi_nand_init(this);
	if (ret)
		goto exit_nfc_init;

	pm_runtime_mark_last_busy(&pdev->dev);
	pm_runtime_put_autosuspend(&pdev->dev);

	dev_info(this->dev, "driver registered.\n");

	return 0;

exit_nfc_init:
	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	release_resources(this);
exit_acquire_resources:

	return ret;
}