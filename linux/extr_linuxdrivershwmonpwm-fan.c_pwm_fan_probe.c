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
struct TYPE_7__ {scalar_t__ period; } ;
struct thermal_cooling_device {TYPE_1__ args; } ;
struct pwm_state {int enabled; scalar_t__ duty_cycle; } ;
struct pwm_fan_ctx {struct thermal_cooling_device* pwm; struct thermal_cooling_device* cdev; int /*<<< orphan*/  pwm_fan_max_state; int /*<<< orphan*/  pwm_fan_state; int /*<<< orphan*/  pwm_value; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device {TYPE_1__ args; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THERMAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  MAX_PWM ; 
 int PTR_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct thermal_cooling_device* devm_hwmon_device_register_with_groups (TYPE_2__*,char*,struct pwm_fan_ctx*,int /*<<< orphan*/ ) ; 
 struct pwm_fan_ctx* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct thermal_cooling_device* devm_of_pwm_get (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pwm_fan_ctx*) ; 
 int pwm_apply_state (struct thermal_cooling_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_fan_cooling_ops ; 
 int /*<<< orphan*/  pwm_fan_groups ; 
 int pwm_fan_of_get_cooling_data (TYPE_2__*,struct pwm_fan_ctx*) ; 
 int /*<<< orphan*/  pwm_init_state (struct thermal_cooling_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  thermal_cdev_update (struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* thermal_of_cooling_device_register (int /*<<< orphan*/ ,char*,struct pwm_fan_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_fan_probe(struct platform_device *pdev)
{
	struct thermal_cooling_device *cdev;
	struct pwm_fan_ctx *ctx;
	struct device *hwmon;
	int ret;
	struct pwm_state state = { };

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mutex_init(&ctx->lock);

	ctx->pwm = devm_of_pwm_get(&pdev->dev, pdev->dev.of_node, NULL);
	if (IS_ERR(ctx->pwm)) {
		dev_err(&pdev->dev, "Could not get PWM\n");
		return PTR_ERR(ctx->pwm);
	}

	platform_set_drvdata(pdev, ctx);

	ctx->pwm_value = MAX_PWM;

	/* Set duty cycle to maximum allowed and enable PWM output */
	pwm_init_state(ctx->pwm, &state);
	state.duty_cycle = ctx->pwm->args.period - 1;
	state.enabled = true;

	ret = pwm_apply_state(ctx->pwm, &state);
	if (ret) {
		dev_err(&pdev->dev, "Failed to configure PWM\n");
		return ret;
	}

	hwmon = devm_hwmon_device_register_with_groups(&pdev->dev, "pwmfan",
						       ctx, pwm_fan_groups);
	if (IS_ERR(hwmon)) {
		dev_err(&pdev->dev, "Failed to register hwmon device\n");
		ret = PTR_ERR(hwmon);
		goto err_pwm_disable;
	}

	ret = pwm_fan_of_get_cooling_data(&pdev->dev, ctx);
	if (ret)
		return ret;

	ctx->pwm_fan_state = ctx->pwm_fan_max_state;
	if (IS_ENABLED(CONFIG_THERMAL)) {
		cdev = thermal_of_cooling_device_register(pdev->dev.of_node,
							  "pwm-fan", ctx,
							  &pwm_fan_cooling_ops);
		if (IS_ERR(cdev)) {
			dev_err(&pdev->dev,
				"Failed to register pwm-fan as cooling device");
			ret = PTR_ERR(cdev);
			goto err_pwm_disable;
		}
		ctx->cdev = cdev;
		thermal_cdev_update(cdev);
	}

	return 0;

err_pwm_disable:
	state.enabled = false;
	pwm_apply_state(ctx->pwm, &state);

	return ret;
}