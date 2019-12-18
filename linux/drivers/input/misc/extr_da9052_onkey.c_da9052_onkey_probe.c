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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {TYPE_2__* parent; } ;
struct input_dev {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/ * evbit; TYPE_1__ dev; } ;
struct da9052_onkey {int /*<<< orphan*/  work; struct da9052* da9052; struct input_dev* input; } ;
struct da9052 {TYPE_2__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DA9052_IRQ_NONKEY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da9052_free_irq (struct da9052*,int /*<<< orphan*/ ,struct da9052_onkey*) ; 
 int /*<<< orphan*/  da9052_onkey_irq ; 
 int /*<<< orphan*/  da9052_onkey_work ; 
 int da9052_request_irq (struct da9052*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct da9052_onkey*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct da9052* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct da9052_onkey*) ; 
 struct da9052_onkey* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9052_onkey*) ; 

__attribute__((used)) static int da9052_onkey_probe(struct platform_device *pdev)
{
	struct da9052 *da9052 = dev_get_drvdata(pdev->dev.parent);
	struct da9052_onkey *onkey;
	struct input_dev *input_dev;
	int error;

	if (!da9052) {
		dev_err(&pdev->dev, "Failed to get the driver's data\n");
		return -EINVAL;
	}

	onkey = kzalloc(sizeof(*onkey), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!onkey || !input_dev) {
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	onkey->input = input_dev;
	onkey->da9052 = da9052;
	INIT_DELAYED_WORK(&onkey->work, da9052_onkey_work);

	input_dev->name = "da9052-onkey";
	input_dev->phys = "da9052-onkey/input0";
	input_dev->dev.parent = &pdev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	__set_bit(KEY_POWER, input_dev->keybit);

	error = da9052_request_irq(onkey->da9052, DA9052_IRQ_NONKEY, "ONKEY",
			    da9052_onkey_irq, onkey);
	if (error < 0) {
		dev_err(onkey->da9052->dev,
			"Failed to register ONKEY IRQ: %d\n", error);
		goto err_free_mem;
	}

	error = input_register_device(onkey->input);
	if (error) {
		dev_err(&pdev->dev, "Unable to register input device, %d\n",
			error);
		goto err_free_irq;
	}

	platform_set_drvdata(pdev, onkey);
	return 0;

err_free_irq:
	da9052_free_irq(onkey->da9052, DA9052_IRQ_NONKEY, onkey);
	cancel_delayed_work_sync(&onkey->work);
err_free_mem:
	input_free_device(input_dev);
	kfree(onkey);

	return error;
}