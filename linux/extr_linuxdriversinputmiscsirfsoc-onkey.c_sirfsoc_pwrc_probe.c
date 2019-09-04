#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sirfsoc_pwrc_drvdata {TYPE_1__* input; int /*<<< orphan*/  work; int /*<<< orphan*/  pwrc_base; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {char* name; char* phys; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/ * evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct sirfsoc_pwrc_drvdata*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_4__*,int) ; 
 TYPE_1__* devm_input_allocate_device (TYPE_4__*) ; 
 struct sirfsoc_pwrc_drvdata* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sirfsoc_pwrc_drvdata*) ; 
 int input_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_1__*,struct sirfsoc_pwrc_drvdata*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_pwrc_close ; 
 int /*<<< orphan*/  sirfsoc_pwrc_isr ; 
 int /*<<< orphan*/  sirfsoc_pwrc_open ; 
 int /*<<< orphan*/  sirfsoc_pwrc_report_event ; 
 int /*<<< orphan*/  sirfsoc_pwrc_toggle_interrupts (struct sirfsoc_pwrc_drvdata*,int) ; 

__attribute__((used)) static int sirfsoc_pwrc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sirfsoc_pwrc_drvdata *pwrcdrv;
	int irq;
	int error;

	pwrcdrv = devm_kzalloc(&pdev->dev, sizeof(struct sirfsoc_pwrc_drvdata),
			       GFP_KERNEL);
	if (!pwrcdrv) {
		dev_info(&pdev->dev, "Not enough memory for the device data\n");
		return -ENOMEM;
	}

	/*
	 * We can't use of_iomap because pwrc is not mapped in memory,
	 * the so-called base address is only offset in rtciobrg
	 */
	error = of_property_read_u32(np, "reg", &pwrcdrv->pwrc_base);
	if (error) {
		dev_err(&pdev->dev,
			"unable to find base address of pwrc node in dtb\n");
		return error;
	}

	pwrcdrv->input = devm_input_allocate_device(&pdev->dev);
	if (!pwrcdrv->input)
		return -ENOMEM;

	pwrcdrv->input->name = "sirfsoc pwrckey";
	pwrcdrv->input->phys = "pwrc/input0";
	pwrcdrv->input->evbit[0] = BIT_MASK(EV_KEY);
	input_set_capability(pwrcdrv->input, EV_KEY, KEY_POWER);

	INIT_DELAYED_WORK(&pwrcdrv->work, sirfsoc_pwrc_report_event);

	pwrcdrv->input->open = sirfsoc_pwrc_open;
	pwrcdrv->input->close = sirfsoc_pwrc_close;

	input_set_drvdata(pwrcdrv->input, pwrcdrv);

	/* Make sure the device is quiesced */
	sirfsoc_pwrc_toggle_interrupts(pwrcdrv, false);

	irq = platform_get_irq(pdev, 0);
	error = devm_request_irq(&pdev->dev, irq,
				 sirfsoc_pwrc_isr, 0,
				 "sirfsoc_pwrc_int", pwrcdrv);
	if (error) {
		dev_err(&pdev->dev, "unable to claim irq %d, error: %d\n",
			irq, error);
		return error;
	}

	error = input_register_device(pwrcdrv->input);
	if (error) {
		dev_err(&pdev->dev,
			"unable to register input device, error: %d\n",
			error);
		return error;
	}

	dev_set_drvdata(&pdev->dev, pwrcdrv);
	device_init_wakeup(&pdev->dev, 1);

	return 0;
}