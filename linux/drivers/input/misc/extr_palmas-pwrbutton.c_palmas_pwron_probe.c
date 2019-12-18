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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct palmas_pwron_config {int long_press_time_val; int pwron_debounce_val; } ;
struct palmas_pwron {int /*<<< orphan*/  irq; int /*<<< orphan*/  input_work; struct input_dev* input_dev; struct palmas* palmas; } ;
struct palmas {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct input_dev {char* name; char* phys; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  PALMAS_LONG_PRESS_KEY ; 
 int PALMAS_LPK_TIME_MASK ; 
 int /*<<< orphan*/  PALMAS_PMU_CONTROL_BASE ; 
 int PALMAS_PWRON_DEBOUNCE_MASK ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct palmas* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct palmas_pwron*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct palmas_pwron*) ; 
 struct palmas_pwron* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palmas_power_button_work ; 
 int /*<<< orphan*/  palmas_pwron_params_ofinit (struct device*,struct palmas_pwron_config*) ; 
 int palmas_update_bits (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct palmas_pwron*) ; 
 int /*<<< orphan*/  pwron_irq ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct palmas_pwron*) ; 

__attribute__((used)) static int palmas_pwron_probe(struct platform_device *pdev)
{
	struct palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct input_dev *input_dev;
	struct palmas_pwron *pwron;
	struct palmas_pwron_config config;
	int val;
	int error;

	palmas_pwron_params_ofinit(dev, &config);

	pwron = kzalloc(sizeof(*pwron), GFP_KERNEL);
	if (!pwron)
		return -ENOMEM;

	input_dev = input_allocate_device();
	if (!input_dev) {
		dev_err(dev, "Can't allocate power button\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	input_dev->name = "palmas_pwron";
	input_dev->phys = "palmas_pwron/input0";
	input_dev->dev.parent = dev;

	input_set_capability(input_dev, EV_KEY, KEY_POWER);

	/*
	 * Setup default hardware shutdown option (long key press)
	 * and debounce.
	 */
	val = config.long_press_time_val << __ffs(PALMAS_LPK_TIME_MASK);
	val |= config.pwron_debounce_val << __ffs(PALMAS_PWRON_DEBOUNCE_MASK);
	error = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
				   PALMAS_LONG_PRESS_KEY,
				   PALMAS_LPK_TIME_MASK |
					PALMAS_PWRON_DEBOUNCE_MASK,
				   val);
	if (error) {
		dev_err(dev, "LONG_PRESS_KEY_UPDATE failed: %d\n", error);
		goto err_free_input;
	}

	pwron->palmas = palmas;
	pwron->input_dev = input_dev;

	INIT_DELAYED_WORK(&pwron->input_work, palmas_power_button_work);

	pwron->irq = platform_get_irq(pdev, 0);
	error = request_threaded_irq(pwron->irq, NULL, pwron_irq,
				     IRQF_TRIGGER_HIGH |
					IRQF_TRIGGER_LOW |
					IRQF_ONESHOT,
				     dev_name(dev), pwron);
	if (error) {
		dev_err(dev, "Can't get IRQ for pwron: %d\n", error);
		goto err_free_input;
	}

	error = input_register_device(input_dev);
	if (error) {
		dev_err(dev, "Can't register power button: %d\n", error);
		goto err_free_irq;
	}

	platform_set_drvdata(pdev, pwron);
	device_init_wakeup(dev, true);

	return 0;

err_free_irq:
	cancel_delayed_work_sync(&pwron->input_work);
	free_irq(pwron->irq, pwron);
err_free_input:
	input_free_device(input_dev);
err_free_mem:
	kfree(pwron);
	return error;
}