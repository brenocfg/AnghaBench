#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_8__ dev; } ;
struct max77693_haptic {int suspend_state; int dev_type; TYPE_4__* input_dev; int /*<<< orphan*/  motor_reg; int /*<<< orphan*/  pwm_dev; int /*<<< orphan*/  work; int /*<<< orphan*/  regmap_haptic; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; TYPE_8__* dev; int /*<<< orphan*/  regmap_pmic; } ;
struct max77693_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regmap_haptic; } ;
struct TYPE_15__ {TYPE_8__* parent; } ;
struct TYPE_14__ {int version; } ;
struct TYPE_17__ {char* name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; } ;
struct TYPE_16__ {int driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX77693_HAPTIC_EXTERNAL_MODE ; 
 int /*<<< orphan*/  MAX77693_HAPTIC_LRA ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  TYPE_MAX77693 129 
#define  TYPE_MAX77843 128 
 int /*<<< orphan*/  dev_err (TYPE_8__*,char*,...) ; 
 struct max77693_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_4__* devm_input_allocate_device (TYPE_8__*) ; 
 struct max77693_haptic* devm_kzalloc (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pwm_get (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_8__*,char*) ; 
 int input_ff_create_memless (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_4__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_4__*,struct max77693_haptic*) ; 
 int /*<<< orphan*/  max77693_haptic_close ; 
 int /*<<< orphan*/  max77693_haptic_open ; 
 int /*<<< orphan*/  max77693_haptic_play_effect ; 
 int /*<<< orphan*/  max77693_haptic_play_work ; 
 TYPE_3__* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max77693_haptic*) ; 
 int /*<<< orphan*/  pwm_apply_args (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77693_haptic_probe(struct platform_device *pdev)
{
	struct max77693_dev *max77693 = dev_get_drvdata(pdev->dev.parent);
	struct max77693_haptic *haptic;
	int error;

	haptic = devm_kzalloc(&pdev->dev, sizeof(*haptic), GFP_KERNEL);
	if (!haptic)
		return -ENOMEM;

	haptic->regmap_pmic = max77693->regmap;
	haptic->dev = &pdev->dev;
	haptic->type = MAX77693_HAPTIC_LRA;
	haptic->mode = MAX77693_HAPTIC_EXTERNAL_MODE;
	haptic->suspend_state = false;

	/* Variant-specific init */
	haptic->dev_type = platform_get_device_id(pdev)->driver_data;
	switch (haptic->dev_type) {
	case TYPE_MAX77693:
		haptic->regmap_haptic = max77693->regmap_haptic;
		break;
	case TYPE_MAX77843:
		haptic->regmap_haptic = max77693->regmap;
		break;
	default:
		dev_err(&pdev->dev, "unsupported device type: %u\n",
			haptic->dev_type);
		return -EINVAL;
	}

	INIT_WORK(&haptic->work, max77693_haptic_play_work);

	/* Get pwm and regulatot for haptic device */
	haptic->pwm_dev = devm_pwm_get(&pdev->dev, NULL);
	if (IS_ERR(haptic->pwm_dev)) {
		dev_err(&pdev->dev, "failed to get pwm device\n");
		return PTR_ERR(haptic->pwm_dev);
	}

	/*
	 * FIXME: pwm_apply_args() should be removed when switching to the
	 * atomic PWM API.
	 */
	pwm_apply_args(haptic->pwm_dev);

	haptic->motor_reg = devm_regulator_get(&pdev->dev, "haptic");
	if (IS_ERR(haptic->motor_reg)) {
		dev_err(&pdev->dev, "failed to get regulator\n");
		return PTR_ERR(haptic->motor_reg);
	}

	/* Initialize input device for haptic device */
	haptic->input_dev = devm_input_allocate_device(&pdev->dev);
	if (!haptic->input_dev) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	haptic->input_dev->name = "max77693-haptic";
	haptic->input_dev->id.version = 1;
	haptic->input_dev->dev.parent = &pdev->dev;
	haptic->input_dev->open = max77693_haptic_open;
	haptic->input_dev->close = max77693_haptic_close;
	input_set_drvdata(haptic->input_dev, haptic);
	input_set_capability(haptic->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptic->input_dev, NULL,
				max77693_haptic_play_effect);
	if (error) {
		dev_err(&pdev->dev, "failed to create force-feedback\n");
		return error;
	}

	error = input_register_device(haptic->input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	platform_set_drvdata(pdev, haptic);

	return 0;
}