#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct max8925_onkey_info {int* irq; struct input_dev* idev; TYPE_3__* dev; int /*<<< orphan*/  i2c; } ;
struct max8925_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct max8925_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 struct max8925_onkey_info* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max8925_onkey_info*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_onkey_handler ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8925_onkey_info*) ; 

__attribute__((used)) static int max8925_onkey_probe(struct platform_device *pdev)
{
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct max8925_onkey_info *info;
	struct input_dev *input;
	int irq[2], error;

	irq[0] = platform_get_irq(pdev, 0);
	if (irq[0] < 0)
		return -EINVAL;

	irq[1] = platform_get_irq(pdev, 1);
	if (irq[1] < 0)
		return -EINVAL;

	info = devm_kzalloc(&pdev->dev, sizeof(struct max8925_onkey_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	info->idev = input;
	info->i2c = chip->i2c;
	info->dev = &pdev->dev;
	info->irq[0] = irq[0];
	info->irq[1] = irq[1];

	input->name = "max8925_on";
	input->phys = "max8925_on/input0";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &pdev->dev;
	input_set_capability(input, EV_KEY, KEY_POWER);

	error = devm_request_threaded_irq(&pdev->dev, irq[0], NULL,
					  max8925_onkey_handler, IRQF_ONESHOT,
					  "onkey-down", info);
	if (error < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			irq[0], error);
		return error;
	}

	error = devm_request_threaded_irq(&pdev->dev, irq[1], NULL,
					  max8925_onkey_handler, IRQF_ONESHOT,
					  "onkey-up", info);
	if (error < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			irq[1], error);
		return error;
	}

	error = input_register_device(info->idev);
	if (error) {
		dev_err(chip->dev, "Can't register input device: %d\n", error);
		return error;
	}

	platform_set_drvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	return 0;
}