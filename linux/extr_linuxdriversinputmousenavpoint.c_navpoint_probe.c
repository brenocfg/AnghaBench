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
struct ssp_device {int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct navpoint_platform_data {int /*<<< orphan*/  gpio; int /*<<< orphan*/  port; } ;
struct navpoint {int /*<<< orphan*/  gpio; int /*<<< orphan*/ * dev; struct input_dev* input; struct ssp_device* ssp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  NAVPOINT_PRESSURE_MAX ; 
 int /*<<< orphan*/  NAVPOINT_PRESSURE_MIN ; 
 int /*<<< orphan*/  NAVPOINT_X_MAX ; 
 int /*<<< orphan*/  NAVPOINT_X_MIN ; 
 int /*<<< orphan*/  NAVPOINT_Y_MAX ; 
 int /*<<< orphan*/  NAVPOINT_Y_MIN ; 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct navpoint_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct navpoint*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct navpoint*) ; 
 int /*<<< orphan*/  kfree (struct navpoint*) ; 
 struct navpoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  navpoint_close ; 
 int /*<<< orphan*/  navpoint_irq ; 
 int /*<<< orphan*/  navpoint_open ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct navpoint*) ; 
 int /*<<< orphan*/  pxa_ssp_free (struct ssp_device*) ; 
 int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 struct ssp_device* pxa_ssp_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct navpoint*) ; 

__attribute__((used)) static int navpoint_probe(struct platform_device *pdev)
{
	const struct navpoint_platform_data *pdata =
					dev_get_platdata(&pdev->dev);
	struct ssp_device *ssp;
	struct input_dev *input;
	struct navpoint *navpoint;
	int error;

	if (!pdata) {
		dev_err(&pdev->dev, "no platform data\n");
		return -EINVAL;
	}

	if (gpio_is_valid(pdata->gpio)) {
		error = gpio_request_one(pdata->gpio, GPIOF_OUT_INIT_LOW,
					 "SYNAPTICS_ON");
		if (error)
			return error;
	}

	ssp = pxa_ssp_request(pdata->port, pdev->name);
	if (!ssp) {
		error = -ENODEV;
		goto err_free_gpio;
	}

	/* HaRET does not disable devices before jumping into Linux */
	if (pxa_ssp_read_reg(ssp, SSCR0) & SSCR0_SSE) {
		pxa_ssp_write_reg(ssp, SSCR0, 0);
		dev_warn(&pdev->dev, "ssp%d already enabled\n", pdata->port);
	}

	navpoint = kzalloc(sizeof(*navpoint), GFP_KERNEL);
	input = input_allocate_device();
	if (!navpoint || !input) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	navpoint->ssp = ssp;
	navpoint->input = input;
	navpoint->dev = &pdev->dev;
	navpoint->gpio = pdata->gpio;

	input->name = pdev->name;
	input->dev.parent = &pdev->dev;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(EV_ABS, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(BTN_TOUCH, input->keybit);
	__set_bit(BTN_TOOL_FINGER, input->keybit);

	input_set_abs_params(input, ABS_X,
			     NAVPOINT_X_MIN, NAVPOINT_X_MAX, 0, 0);
	input_set_abs_params(input, ABS_Y,
			     NAVPOINT_Y_MIN, NAVPOINT_Y_MAX, 0, 0);
	input_set_abs_params(input, ABS_PRESSURE,
			     NAVPOINT_PRESSURE_MIN, NAVPOINT_PRESSURE_MAX,
			     0, 0);

	input->open = navpoint_open;
	input->close = navpoint_close;

	input_set_drvdata(input, navpoint);

	error = request_irq(ssp->irq, navpoint_irq, 0, pdev->name, navpoint);
	if (error)
		goto err_free_mem;

	error = input_register_device(input);
	if (error)
		goto err_free_irq;

	platform_set_drvdata(pdev, navpoint);
	dev_dbg(&pdev->dev, "ssp%d, irq %d\n", pdata->port, ssp->irq);

	return 0;

err_free_irq:
	free_irq(ssp->irq, navpoint);
err_free_mem:
	input_free_device(input);
	kfree(navpoint);
	pxa_ssp_free(ssp);
err_free_gpio:
	if (gpio_is_valid(pdata->gpio))
		gpio_free(pdata->gpio);

	return error;
}