#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pwrkey_drv_data {scalar_t__ irq; int /*<<< orphan*/  wakeup; struct input_dev* input; int /*<<< orphan*/  keycode; int /*<<< orphan*/  check_timer; int /*<<< orphan*/  snvs; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* phys; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNVS_LPCR_DEP_EN ; 
 int /*<<< orphan*/  SNVS_LPCR_REG ; 
 int /*<<< orphan*/  SNVS_LPSR_REG ; 
 int /*<<< orphan*/  SNVS_LPSR_SPO ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int dev_pm_set_wake_irq (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int devm_add_action (TYPE_2__*,int /*<<< orphan*/ ,struct pwrkey_drv_data*) ; 
 struct input_dev* devm_input_allocate_device (TYPE_2__*) ; 
 struct pwrkey_drv_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  imx_imx_snvs_check_for_events ; 
 int /*<<< orphan*/  imx_snvs_pwrkey_act ; 
 int /*<<< orphan*/  imx_snvs_pwrkey_interrupt ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pwrkey_drv_data*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_snvs_pwrkey_probe(struct platform_device *pdev)
{
	struct pwrkey_drv_data *pdata = NULL;
	struct input_dev *input = NULL;
	struct device_node *np;
	int error;

	/* Get SNVS register Page */
	np = pdev->dev.of_node;
	if (!np)
		return -ENODEV;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	pdata->snvs = syscon_regmap_lookup_by_phandle(np, "regmap");
	if (IS_ERR(pdata->snvs)) {
		dev_err(&pdev->dev, "Can't get snvs syscon\n");
		return PTR_ERR(pdata->snvs);
	}

	if (of_property_read_u32(np, "linux,keycode", &pdata->keycode)) {
		pdata->keycode = KEY_POWER;
		dev_warn(&pdev->dev, "KEY_POWER without setting in dts\n");
	}

	pdata->wakeup = of_property_read_bool(np, "wakeup-source");

	pdata->irq = platform_get_irq(pdev, 0);
	if (pdata->irq < 0)
		return -EINVAL;

	regmap_update_bits(pdata->snvs, SNVS_LPCR_REG, SNVS_LPCR_DEP_EN, SNVS_LPCR_DEP_EN);

	/* clear the unexpected interrupt before driver ready */
	regmap_write(pdata->snvs, SNVS_LPSR_REG, SNVS_LPSR_SPO);

	timer_setup(&pdata->check_timer, imx_imx_snvs_check_for_events, 0);

	input = devm_input_allocate_device(&pdev->dev);
	if (!input) {
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		return -ENOMEM;
	}

	input->name = pdev->name;
	input->phys = "snvs-pwrkey/input0";
	input->id.bustype = BUS_HOST;

	input_set_capability(input, EV_KEY, pdata->keycode);

	/* input customer action to cancel release timer */
	error = devm_add_action(&pdev->dev, imx_snvs_pwrkey_act, pdata);
	if (error) {
		dev_err(&pdev->dev, "failed to register remove action\n");
		return error;
	}

	pdata->input = input;
	platform_set_drvdata(pdev, pdata);

	error = devm_request_irq(&pdev->dev, pdata->irq,
			       imx_snvs_pwrkey_interrupt,
			       0, pdev->name, pdev);

	if (error) {
		dev_err(&pdev->dev, "interrupt not available.\n");
		return error;
	}

	error = input_register_device(input);
	if (error < 0) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	device_init_wakeup(&pdev->dev, pdata->wakeup);
	error = dev_pm_set_wake_irq(&pdev->dev, pdata->irq);
	if (error)
		dev_err(&pdev->dev, "irq wake enable failed.\n");

	return 0;
}