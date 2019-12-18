#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_vibrator {TYPE_2__* input; int /*<<< orphan*/  play_work; int /*<<< orphan*/  gpio; int /*<<< orphan*/  vcc; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  close; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct gpio_vibrator* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpio_vibrator_close ; 
 int /*<<< orphan*/  gpio_vibrator_play_effect ; 
 int /*<<< orphan*/  gpio_vibrator_play_work ; 
 int input_ff_create_memless (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct gpio_vibrator*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_vibrator*) ; 

__attribute__((used)) static int gpio_vibrator_probe(struct platform_device *pdev)
{
	struct gpio_vibrator *vibrator;
	int err;

	vibrator = devm_kzalloc(&pdev->dev, sizeof(*vibrator), GFP_KERNEL);
	if (!vibrator)
		return -ENOMEM;

	vibrator->input = devm_input_allocate_device(&pdev->dev);
	if (!vibrator->input)
		return -ENOMEM;

	vibrator->vcc = devm_regulator_get(&pdev->dev, "vcc");
	err = PTR_ERR_OR_ZERO(vibrator->vcc);
	if (err) {
		if (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to request regulator: %d\n",
				err);
		return err;
	}

	vibrator->gpio = devm_gpiod_get(&pdev->dev, "enable", GPIOD_OUT_LOW);
	err = PTR_ERR_OR_ZERO(vibrator->gpio);
	if (err) {
		if (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to request main gpio: %d\n",
				err);
		return err;
	}

	INIT_WORK(&vibrator->play_work, gpio_vibrator_play_work);

	vibrator->input->name = "gpio-vibrator";
	vibrator->input->id.bustype = BUS_HOST;
	vibrator->input->close = gpio_vibrator_close;

	input_set_drvdata(vibrator->input, vibrator);
	input_set_capability(vibrator->input, EV_FF, FF_RUMBLE);

	err = input_ff_create_memless(vibrator->input, NULL,
				      gpio_vibrator_play_effect);
	if (err) {
		dev_err(&pdev->dev, "Couldn't create FF dev: %d\n", err);
		return err;
	}

	err = input_register_device(vibrator->input);
	if (err) {
		dev_err(&pdev->dev, "Couldn't register input dev: %d\n", err);
		return err;
	}

	platform_set_drvdata(pdev, vibrator);

	return 0;
}