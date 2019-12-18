#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pm860x_onkey_info {int irq; TYPE_3__* idev; TYPE_4__* dev; int /*<<< orphan*/  i2c; struct pm860x_chip* chip; } ;
struct pm860x_chip {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  companion; int /*<<< orphan*/  client; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_10__ {TYPE_4__* parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_11__ {char* name; char* phys; void** keybit; void** evbit; TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 void* BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_I2C ; 
 scalar_t__ CHIP_PM8607 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct pm860x_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_4__*,int) ; 
 TYPE_3__* devm_input_allocate_device (TYPE_4__*) ; 
 struct pm860x_onkey_info* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pm860x_onkey_info*) ; 
 int input_register_device (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm860x_onkey_info*) ; 
 int /*<<< orphan*/  pm860x_onkey_handler ; 

__attribute__((used)) static int pm860x_onkey_probe(struct platform_device *pdev)
{
	struct pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct pm860x_onkey_info *info;
	int irq, ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EINVAL;

	info = devm_kzalloc(&pdev->dev, sizeof(struct pm860x_onkey_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->chip = chip;
	info->i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->dev = &pdev->dev;
	info->irq = irq;

	info->idev = devm_input_allocate_device(&pdev->dev);
	if (!info->idev) {
		dev_err(chip->dev, "Failed to allocate input dev\n");
		return -ENOMEM;
	}

	info->idev->name = "88pm860x_on";
	info->idev->phys = "88pm860x_on/input0";
	info->idev->id.bustype = BUS_I2C;
	info->idev->dev.parent = &pdev->dev;
	info->idev->evbit[0] = BIT_MASK(EV_KEY);
	info->idev->keybit[BIT_WORD(KEY_POWER)] = BIT_MASK(KEY_POWER);

	ret = input_register_device(info->idev);
	if (ret) {
		dev_err(chip->dev, "Can't register input device: %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(&pdev->dev, info->irq, NULL,
					pm860x_onkey_handler, IRQF_ONESHOT,
					"onkey", info);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		return ret;
	}

	platform_set_drvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	return 0;
}