#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qoriq_tmu_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  little_endian; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get_optional (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct qoriq_tmu_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qoriq_tmu_data*) ; 
 int qoriq_tmu_calibration (struct platform_device*) ; 
 int /*<<< orphan*/  qoriq_tmu_init_device (struct qoriq_tmu_data*) ; 
 int qoriq_tmu_register_tmu_zone (struct platform_device*) ; 

__attribute__((used)) static int qoriq_tmu_probe(struct platform_device *pdev)
{
	int ret;
	struct qoriq_tmu_data *data;
	struct device_node *np = pdev->dev.of_node;

	data = devm_kzalloc(&pdev->dev, sizeof(struct qoriq_tmu_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);

	data->little_endian = of_property_read_bool(np, "little-endian");

	data->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(data->regs)) {
		dev_err(&pdev->dev, "Failed to get memory region\n");
		return PTR_ERR(data->regs);
	}

	data->clk = devm_clk_get_optional(&pdev->dev, NULL);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	if (ret) {
		dev_err(&pdev->dev, "Failed to enable clock\n");
		return ret;
	}

	qoriq_tmu_init_device(data);	/* TMU initialization */

	ret = qoriq_tmu_calibration(pdev);	/* TMU calibration */
	if (ret < 0)
		goto err;

	ret = qoriq_tmu_register_tmu_zone(pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register sensors\n");
		ret = -ENODEV;
		goto err;
	}

	return 0;

err:
	clk_disable_unprepare(data->clk);
	platform_set_drvdata(pdev, NULL);

	return ret;
}