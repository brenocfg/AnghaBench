#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ab8500_gpadc {scalar_t__ irq_sw; scalar_t__ irq_hw; TYPE_1__* dev; int /*<<< orphan*/  node; int /*<<< orphan*/  regu; int /*<<< orphan*/  ab8500_gpadc_complete; int /*<<< orphan*/  ab8500_gpadc_lock; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPADC_AUDOSUSPEND_DELAY ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ab8500_bm_gpadcconvend_handler ; 
 int /*<<< orphan*/  ab8500_gpadc_list ; 
 int /*<<< orphan*/  ab8500_gpadc_read_calibration_data (struct ab8500_gpadc*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct ab8500_gpadc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free_irq (int,struct ab8500_gpadc*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ab8500_gpadc*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct ab8500_gpadc*) ; 

__attribute__((used)) static int ab8500_gpadc_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct ab8500_gpadc *gpadc;

	gpadc = devm_kzalloc(&pdev->dev,
			     sizeof(struct ab8500_gpadc), GFP_KERNEL);
	if (!gpadc)
		return -ENOMEM;

	gpadc->irq_sw = platform_get_irq_byname(pdev, "SW_CONV_END");
	if (gpadc->irq_sw < 0)
		dev_err(gpadc->dev, "failed to get platform sw_conv_end irq\n");

	gpadc->irq_hw = platform_get_irq_byname(pdev, "HW_CONV_END");
	if (gpadc->irq_hw < 0)
		dev_err(gpadc->dev, "failed to get platform hw_conv_end irq\n");

	gpadc->dev = &pdev->dev;
	gpadc->parent = dev_get_drvdata(pdev->dev.parent);
	mutex_init(&gpadc->ab8500_gpadc_lock);

	/* Initialize completion used to notify completion of conversion */
	init_completion(&gpadc->ab8500_gpadc_complete);

	/* Register interrupts */
	if (gpadc->irq_sw >= 0) {
		ret = request_threaded_irq(gpadc->irq_sw, NULL,
			ab8500_bm_gpadcconvend_handler,
			IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
			"ab8500-gpadc-sw",
			gpadc);
		if (ret < 0) {
			dev_err(gpadc->dev,
				"Failed to register interrupt irq: %d\n",
				gpadc->irq_sw);
			goto fail;
		}
	}

	if (gpadc->irq_hw >= 0) {
		ret = request_threaded_irq(gpadc->irq_hw, NULL,
			ab8500_bm_gpadcconvend_handler,
			IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
			"ab8500-gpadc-hw",
			gpadc);
		if (ret < 0) {
			dev_err(gpadc->dev,
				"Failed to register interrupt irq: %d\n",
				gpadc->irq_hw);
			goto fail_irq;
		}
	}

	/* VTVout LDO used to power up ab8500-GPADC */
	gpadc->regu = devm_regulator_get(&pdev->dev, "vddadc");
	if (IS_ERR(gpadc->regu)) {
		ret = PTR_ERR(gpadc->regu);
		dev_err(gpadc->dev, "failed to get vtvout LDO\n");
		goto fail_irq;
	}

	platform_set_drvdata(pdev, gpadc);

	ret = regulator_enable(gpadc->regu);
	if (ret) {
		dev_err(gpadc->dev, "Failed to enable vtvout LDO: %d\n", ret);
		goto fail_enable;
	}

	pm_runtime_set_autosuspend_delay(gpadc->dev, GPADC_AUDOSUSPEND_DELAY);
	pm_runtime_use_autosuspend(gpadc->dev);
	pm_runtime_set_active(gpadc->dev);
	pm_runtime_enable(gpadc->dev);

	ab8500_gpadc_read_calibration_data(gpadc);
	list_add_tail(&gpadc->node, &ab8500_gpadc_list);
	dev_dbg(gpadc->dev, "probe success\n");

	return 0;

fail_enable:
fail_irq:
	free_irq(gpadc->irq_sw, gpadc);
	free_irq(gpadc->irq_hw, gpadc);
fail:
	return ret;
}