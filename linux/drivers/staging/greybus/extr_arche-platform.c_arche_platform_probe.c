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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct arche_platform_drvdata {int /*<<< orphan*/  platform_state_mutex; TYPE_1__ pm_notifier; int /*<<< orphan*/  wake_detect_irq; void* wake_detect; int /*<<< orphan*/  wake_lock; struct device* dev; int /*<<< orphan*/  num_apbs; void* svc_ref_clk; void* svc_refclk_req; void* svc_sysboot; void* svc_reset; scalar_t__ is_reset_act_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHE_PLATFORM_STATE_OFF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int GPIOD_IN ; 
 unsigned int GPIOD_OUT_HIGH ; 
 unsigned int GPIOD_OUT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  WD_STATE_IDLE ; 
 int arche_platform_coldboot_seq (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_platform_pm_notifier ; 
 int /*<<< orphan*/  arche_platform_set_state (struct arche_platform_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arche_platform_set_wake_detect_state (struct arche_platform_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arche_platform_wd_irq ; 
 int /*<<< orphan*/  arche_platform_wd_irq_en (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_platform_wd_irq_thread ; 
 int /*<<< orphan*/  dev_attr_state ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,unsigned int) ; 
 struct arche_platform_drvdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_child_count (struct device_node*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct arche_platform_drvdata*) ; 
 int register_pm_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arche_platform_probe(struct platform_device *pdev)
{
	struct arche_platform_drvdata *arche_pdata;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;
	unsigned int flags;

	arche_pdata = devm_kzalloc(&pdev->dev, sizeof(*arche_pdata),
				   GFP_KERNEL);
	if (!arche_pdata)
		return -ENOMEM;

	/* setup svc reset gpio */
	arche_pdata->is_reset_act_hi = of_property_read_bool(np,
							     "svc,reset-active-high");
	if (arche_pdata->is_reset_act_hi)
		flags = GPIOD_OUT_HIGH;
	else
		flags = GPIOD_OUT_LOW;

	arche_pdata->svc_reset = devm_gpiod_get(dev, "svc,reset", flags);
	if (IS_ERR(arche_pdata->svc_reset)) {
		ret = PTR_ERR(arche_pdata->svc_reset);
		dev_err(dev, "failed to request svc-reset GPIO: %d\n", ret);
		return ret;
	}
	arche_platform_set_state(arche_pdata, ARCHE_PLATFORM_STATE_OFF);

	arche_pdata->svc_sysboot = devm_gpiod_get(dev, "svc,sysboot",
						  GPIOD_OUT_LOW);
	if (IS_ERR(arche_pdata->svc_sysboot)) {
		ret = PTR_ERR(arche_pdata->svc_sysboot);
		dev_err(dev, "failed to request sysboot0 GPIO: %d\n", ret);
		return ret;
	}

	/* setup the clock request gpio first */
	arche_pdata->svc_refclk_req = devm_gpiod_get(dev, "svc,refclk-req",
						     GPIOD_IN);
	if (IS_ERR(arche_pdata->svc_refclk_req)) {
		ret = PTR_ERR(arche_pdata->svc_refclk_req);
		dev_err(dev, "failed to request svc-clk-req GPIO: %d\n", ret);
		return ret;
	}

	/* setup refclk2 to follow the pin */
	arche_pdata->svc_ref_clk = devm_clk_get(dev, "svc_ref_clk");
	if (IS_ERR(arche_pdata->svc_ref_clk)) {
		ret = PTR_ERR(arche_pdata->svc_ref_clk);
		dev_err(dev, "failed to get svc_ref_clk: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, arche_pdata);

	arche_pdata->num_apbs = of_get_child_count(np);
	dev_dbg(dev, "Number of APB's available - %d\n", arche_pdata->num_apbs);

	arche_pdata->wake_detect = devm_gpiod_get(dev, "svc,wake-detect",
						  GPIOD_IN);
	if (IS_ERR(arche_pdata->wake_detect)) {
		ret = PTR_ERR(arche_pdata->wake_detect);
		dev_err(dev, "Failed requesting wake_detect GPIO: %d\n", ret);
		return ret;
	}

	arche_platform_set_wake_detect_state(arche_pdata, WD_STATE_IDLE);

	arche_pdata->dev = &pdev->dev;

	spin_lock_init(&arche_pdata->wake_lock);
	mutex_init(&arche_pdata->platform_state_mutex);
	arche_pdata->wake_detect_irq =
		gpiod_to_irq(arche_pdata->wake_detect);

	ret = devm_request_threaded_irq(dev, arche_pdata->wake_detect_irq,
					arche_platform_wd_irq,
					arche_platform_wd_irq_thread,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(dev), arche_pdata);
	if (ret) {
		dev_err(dev, "failed to request wake detect IRQ %d\n", ret);
		return ret;
	}
	disable_irq(arche_pdata->wake_detect_irq);

	ret = device_create_file(dev, &dev_attr_state);
	if (ret) {
		dev_err(dev, "failed to create state file in sysfs\n");
		return ret;
	}

	ret = of_platform_populate(np, NULL, NULL, dev);
	if (ret) {
		dev_err(dev, "failed to populate child nodes %d\n", ret);
		goto err_device_remove;
	}

	arche_pdata->pm_notifier.notifier_call = arche_platform_pm_notifier;
	ret = register_pm_notifier(&arche_pdata->pm_notifier);

	if (ret) {
		dev_err(dev, "failed to register pm notifier %d\n", ret);
		goto err_device_remove;
	}

	/* Explicitly power off if requested */
	if (!of_property_read_bool(pdev->dev.of_node, "arche,init-off")) {
		mutex_lock(&arche_pdata->platform_state_mutex);
		ret = arche_platform_coldboot_seq(arche_pdata);
		if (ret) {
			dev_err(dev, "Failed to cold boot svc %d\n", ret);
			goto err_coldboot;
		}
		arche_platform_wd_irq_en(arche_pdata);
		mutex_unlock(&arche_pdata->platform_state_mutex);
	}

	dev_info(dev, "Device registered successfully\n");
	return 0;

err_coldboot:
	mutex_unlock(&arche_pdata->platform_state_mutex);
err_device_remove:
	device_remove_file(&pdev->dev, &dev_attr_state);
	return ret;
}