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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct opencores_kbd {int* keycodes; int /*<<< orphan*/  addr; struct input_dev* input; } ;
struct TYPE_2__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* phys; int* keycode; int keycodesize; int keycodemax; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct opencores_kbd* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct opencores_kbd*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  opencores_kbd_isr ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opencores_kbd_probe(struct platform_device *pdev)
{
	struct input_dev *input;
	struct opencores_kbd *opencores_kbd;
	struct resource *res;
	int irq, i, error;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "missing board memory resource\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EINVAL;

	opencores_kbd = devm_kzalloc(&pdev->dev, sizeof(*opencores_kbd),
				     GFP_KERNEL);
	if (!opencores_kbd)
		return -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	if (!input) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	opencores_kbd->input = input;

	opencores_kbd->addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(opencores_kbd->addr))
		return PTR_ERR(opencores_kbd->addr);

	input->name = pdev->name;
	input->phys = "opencores-kbd/input0";

	input->id.bustype = BUS_HOST;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	input->keycode = opencores_kbd->keycodes;
	input->keycodesize = sizeof(opencores_kbd->keycodes[0]);
	input->keycodemax = ARRAY_SIZE(opencores_kbd->keycodes);

	__set_bit(EV_KEY, input->evbit);

	for (i = 0; i < ARRAY_SIZE(opencores_kbd->keycodes); i++) {
		/*
		 * OpenCores controller happens to have scancodes match
		 * our KEY_* definitions.
		 */
		opencores_kbd->keycodes[i] = i;
		__set_bit(opencores_kbd->keycodes[i], input->keybit);
	}
	__clear_bit(KEY_RESERVED, input->keybit);

	error = devm_request_irq(&pdev->dev, irq, &opencores_kbd_isr,
				 IRQF_TRIGGER_RISING,
				 pdev->name, opencores_kbd);
	if (error) {
		dev_err(&pdev->dev, "unable to claim irq %d\n", irq);
		return error;
	}

	error = input_register_device(input);
	if (error) {
		dev_err(&pdev->dev, "unable to register input device\n");
		return error;
	}

	return 0;
}