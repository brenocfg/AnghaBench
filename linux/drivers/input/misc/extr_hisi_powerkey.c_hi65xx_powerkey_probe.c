#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct input_dev {char* phys; char* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  KEY_RESTART ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 int devm_request_any_context_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_dev*) ; 
 TYPE_1__* hi65xx_irq_info ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi65xx_powerkey_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct input_dev *input;
	int irq, i, error;

	input = devm_input_allocate_device(dev);
	if (!input) {
		dev_err(dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	input->phys = "hisi_on/input0";
	input->name = "HISI 65xx PowerOn Key";

	input_set_capability(input, EV_KEY, KEY_POWER);
	input_set_capability(input, EV_KEY, KEY_RESTART);

	for (i = 0; i < ARRAY_SIZE(hi65xx_irq_info); i++) {

		irq = platform_get_irq_byname(pdev, hi65xx_irq_info[i].name);
		if (irq < 0)
			return irq;

		error = devm_request_any_context_irq(dev, irq,
						     hi65xx_irq_info[i].handler,
						     IRQF_ONESHOT,
						     hi65xx_irq_info[i].name,
						     input);
		if (error < 0) {
			dev_err(dev, "couldn't request irq %s: %d\n",
				hi65xx_irq_info[i].name, error);
			return error;
		}
	}

	error = input_register_device(input);
	if (error) {
		dev_err(dev, "failed to register input device: %d\n", error);
		return error;
	}

	device_init_wakeup(dev, 1);

	return 0;
}