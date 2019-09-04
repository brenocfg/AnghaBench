#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct max8997_platform_data {struct max8997_haptic_platform_data* haptic_pdata; } ;
struct max8997_haptic_platform_data {int mode; int /*<<< orphan*/  pwm_channel_id; int /*<<< orphan*/  pattern_signal_period; int /*<<< orphan*/  pattern_cycle; int /*<<< orphan*/  internal_mode_pattern; int /*<<< orphan*/  pwm_divisor; int /*<<< orphan*/  type; int /*<<< orphan*/  pwm_period; } ;
struct max8997_haptic {int mode; int /*<<< orphan*/  pwm; int /*<<< orphan*/  regulator; int /*<<< orphan*/  pattern_signal_period; int /*<<< orphan*/  pattern_cycle; int /*<<< orphan*/  internal_mode_pattern; int /*<<< orphan*/  pwm_divisor; int /*<<< orphan*/  type; int /*<<< orphan*/  pwm_period; struct input_dev* input_dev; TYPE_3__* dev; int /*<<< orphan*/  client; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct max8997_dev {int /*<<< orphan*/  haptic; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_3__* parent; } ;
struct TYPE_5__ {int version; } ;
struct input_dev {char* name; int /*<<< orphan*/  close; TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  MAX8997_EXTERNAL_MODE 129 
#define  MAX8997_INTERNAL_MODE 128 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct max8997_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct max8997_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int input_ff_create_memless (struct input_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_ff_destroy (struct input_dev*) ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct max8997_haptic*) ; 
 int /*<<< orphan*/  kfree (struct max8997_haptic*) ; 
 struct max8997_haptic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8997_haptic_close ; 
 int /*<<< orphan*/  max8997_haptic_play_effect ; 
 int /*<<< orphan*/  max8997_haptic_play_effect_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8997_haptic*) ; 
 int /*<<< orphan*/  pwm_apply_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regulator_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8997_haptic_probe(struct platform_device *pdev)
{
	struct max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	const struct max8997_platform_data *pdata =
					dev_get_platdata(iodev->dev);
	const struct max8997_haptic_platform_data *haptic_pdata = NULL;
	struct max8997_haptic *chip;
	struct input_dev *input_dev;
	int error;

	if (pdata)
		haptic_pdata = pdata->haptic_pdata;

	if (!haptic_pdata) {
		dev_err(&pdev->dev, "no haptic platform data\n");
		return -EINVAL;
	}

	chip = kzalloc(sizeof(struct max8997_haptic), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!chip || !input_dev) {
		dev_err(&pdev->dev, "unable to allocate memory\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	INIT_WORK(&chip->work, max8997_haptic_play_effect_work);
	mutex_init(&chip->mutex);

	chip->client = iodev->haptic;
	chip->dev = &pdev->dev;
	chip->input_dev = input_dev;
	chip->pwm_period = haptic_pdata->pwm_period;
	chip->type = haptic_pdata->type;
	chip->mode = haptic_pdata->mode;
	chip->pwm_divisor = haptic_pdata->pwm_divisor;

	switch (chip->mode) {
	case MAX8997_INTERNAL_MODE:
		chip->internal_mode_pattern =
				haptic_pdata->internal_mode_pattern;
		chip->pattern_cycle = haptic_pdata->pattern_cycle;
		chip->pattern_signal_period =
				haptic_pdata->pattern_signal_period;
		break;

	case MAX8997_EXTERNAL_MODE:
		chip->pwm = pwm_request(haptic_pdata->pwm_channel_id,
					"max8997-haptic");
		if (IS_ERR(chip->pwm)) {
			error = PTR_ERR(chip->pwm);
			dev_err(&pdev->dev,
				"unable to request PWM for haptic, error: %d\n",
				error);
			goto err_free_mem;
		}

		/*
		 * FIXME: pwm_apply_args() should be removed when switching to
		 * the atomic PWM API.
		 */
		pwm_apply_args(chip->pwm);
		break;

	default:
		dev_err(&pdev->dev,
			"Invalid chip mode specified (%d)\n", chip->mode);
		error = -EINVAL;
		goto err_free_mem;
	}

	chip->regulator = regulator_get(&pdev->dev, "inmotor");
	if (IS_ERR(chip->regulator)) {
		error = PTR_ERR(chip->regulator);
		dev_err(&pdev->dev,
			"unable to get regulator, error: %d\n",
			error);
		goto err_free_pwm;
	}

	input_dev->name = "max8997-haptic";
	input_dev->id.version = 1;
	input_dev->dev.parent = &pdev->dev;
	input_dev->close = max8997_haptic_close;
	input_set_drvdata(input_dev, chip);
	input_set_capability(input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(input_dev, NULL,
				max8997_haptic_play_effect);
	if (error) {
		dev_err(&pdev->dev,
			"unable to create FF device, error: %d\n",
			error);
		goto err_put_regulator;
	}

	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev,
			"unable to register input device, error: %d\n",
			error);
		goto err_destroy_ff;
	}

	platform_set_drvdata(pdev, chip);
	return 0;

err_destroy_ff:
	input_ff_destroy(input_dev);
err_put_regulator:
	regulator_put(chip->regulator);
err_free_pwm:
	if (chip->mode == MAX8997_EXTERNAL_MODE)
		pwm_free(chip->pwm);
err_free_mem:
	input_free_device(input_dev);
	kfree(chip);

	return error;
}