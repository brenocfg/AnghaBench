#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcf50633_input {int /*<<< orphan*/  pcf; struct input_dev* input_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int* evbit; int /*<<< orphan*/  keybit; TYPE_2__ id; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_PWR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  PCF50633_IRQ_ONKEYF ; 
 int /*<<< orphan*/  PCF50633_IRQ_ONKEYR ; 
 int /*<<< orphan*/  dev_to_pcf50633 (int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct pcf50633_input*) ; 
 struct pcf50633_input* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf50633_input_irq ; 
 int /*<<< orphan*/  pcf50633_register_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcf50633_input*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pcf50633_input*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf50633_input_probe(struct platform_device *pdev)
{
	struct pcf50633_input *input;
	struct input_dev *input_dev;
	int ret;


	input = kzalloc(sizeof(*input), GFP_KERNEL);
	if (!input)
		return -ENOMEM;

	input_dev = input_allocate_device();
	if (!input_dev) {
		kfree(input);
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, input);
	input->pcf = dev_to_pcf50633(pdev->dev.parent);
	input->input_dev = input_dev;

	input_dev->name = "PCF50633 PMU events";
	input_dev->id.bustype = BUS_I2C;
	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_PWR);
	set_bit(KEY_POWER, input_dev->keybit);

	ret = input_register_device(input_dev);
	if (ret) {
		input_free_device(input_dev);
		kfree(input);
		return ret;
	}
	pcf50633_register_irq(input->pcf, PCF50633_IRQ_ONKEYR,
				pcf50633_input_irq, input);
	pcf50633_register_irq(input->pcf, PCF50633_IRQ_ONKEYF,
				pcf50633_input_irq, input);

	return 0;
}