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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ period; } ;
struct thermal_cooling_device {int irq; int pulses_per_revolution; struct thermal_cooling_device* cdev; int /*<<< orphan*/  of_node; int /*<<< orphan*/  pwm_fan_max_state; int /*<<< orphan*/  pwm_fan_state; int /*<<< orphan*/  rpm_timer; int /*<<< orphan*/  sample_start; struct thermal_cooling_device* pwm; TYPE_1__ args; int /*<<< orphan*/  pwm_value; struct thermal_cooling_device* reg_en; int /*<<< orphan*/  lock; } ;
struct pwm_state {int enabled; scalar_t__ duty_cycle; } ;
struct pwm_fan_ctx {int irq; int pulses_per_revolution; struct pwm_fan_ctx* cdev; int /*<<< orphan*/  of_node; int /*<<< orphan*/  pwm_fan_max_state; int /*<<< orphan*/  pwm_fan_state; int /*<<< orphan*/  rpm_timer; int /*<<< orphan*/  sample_start; struct pwm_fan_ctx* pwm; TYPE_1__ args; int /*<<< orphan*/  pwm_value; struct pwm_fan_ctx* reg_en; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  name; struct thermal_cooling_device dev; } ;
struct device {int irq; int pulses_per_revolution; struct device* cdev; int /*<<< orphan*/  of_node; int /*<<< orphan*/  pwm_fan_max_state; int /*<<< orphan*/  pwm_fan_state; int /*<<< orphan*/  rpm_timer; int /*<<< orphan*/  sample_start; struct device* pwm; TYPE_1__ args; int /*<<< orphan*/  pwm_value; struct device* reg_en; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THERMAL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HZ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  MAX_PWM ; 
 int PTR_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  dev_err (struct thermal_cooling_device*,char*,...) ; 
 int devm_add_action_or_reset (struct thermal_cooling_device*,int /*<<< orphan*/ ,struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* devm_hwmon_device_register_with_groups (struct thermal_cooling_device*,char*,struct thermal_cooling_device*,int /*<<< orphan*/ ) ; 
 struct thermal_cooling_device* devm_kzalloc (struct thermal_cooling_device*,int,int /*<<< orphan*/ ) ; 
 struct thermal_cooling_device* devm_of_pwm_get (struct thermal_cooling_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct thermal_cooling_device* devm_regulator_get_optional (struct thermal_cooling_device*,char*) ; 
 int devm_request_irq (struct thermal_cooling_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* devm_thermal_of_cooling_device_register (struct thermal_cooling_device*,int /*<<< orphan*/ ,char*,struct thermal_cooling_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq_optional (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  pulse_handler ; 
 int pwm_apply_state (struct thermal_cooling_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_fan_cooling_ops ; 
 int /*<<< orphan*/  pwm_fan_groups ; 
 int pwm_fan_of_get_cooling_data (struct thermal_cooling_device*,struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  pwm_fan_pwm_disable ; 
 int /*<<< orphan*/  pwm_fan_regulator_disable ; 
 int /*<<< orphan*/  pwm_init_state (struct thermal_cooling_device*,struct pwm_state*) ; 
 int regulator_enable (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  sample_timer ; 
 int /*<<< orphan*/  thermal_cdev_update (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwm_fan_probe(struct platform_device *pdev)
{
	struct thermal_cooling_device *cdev;
	struct device *dev = &pdev->dev;
	struct pwm_fan_ctx *ctx;
	struct device *hwmon;
	int ret;
	struct pwm_state state = { };
	u32 ppr = 2;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mutex_init(&ctx->lock);

	ctx->pwm = devm_of_pwm_get(dev, dev->of_node, NULL);
	if (IS_ERR(ctx->pwm)) {
		ret = PTR_ERR(ctx->pwm);

		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Could not get PWM: %d\n", ret);

		return ret;
	}

	platform_set_drvdata(pdev, ctx);

	ctx->irq = platform_get_irq_optional(pdev, 0);
	if (ctx->irq == -EPROBE_DEFER)
		return ctx->irq;

	ctx->reg_en = devm_regulator_get_optional(dev, "fan");
	if (IS_ERR(ctx->reg_en)) {
		if (PTR_ERR(ctx->reg_en) != -ENODEV)
			return PTR_ERR(ctx->reg_en);

		ctx->reg_en = NULL;
	} else {
		ret = regulator_enable(ctx->reg_en);
		if (ret) {
			dev_err(dev, "Failed to enable fan supply: %d\n", ret);
			return ret;
		}
		ret = devm_add_action_or_reset(dev, pwm_fan_regulator_disable,
					       ctx->reg_en);
		if (ret)
			return ret;
	}

	ctx->pwm_value = MAX_PWM;

	/* Set duty cycle to maximum allowed and enable PWM output */
	pwm_init_state(ctx->pwm, &state);
	state.duty_cycle = ctx->pwm->args.period - 1;
	state.enabled = true;

	ret = pwm_apply_state(ctx->pwm, &state);
	if (ret) {
		dev_err(dev, "Failed to configure PWM: %d\n", ret);
		return ret;
	}
	timer_setup(&ctx->rpm_timer, sample_timer, 0);
	ret = devm_add_action_or_reset(dev, pwm_fan_pwm_disable, ctx);
	if (ret)
		return ret;

	of_property_read_u32(dev->of_node, "pulses-per-revolution", &ppr);
	ctx->pulses_per_revolution = ppr;
	if (!ctx->pulses_per_revolution) {
		dev_err(dev, "pulses-per-revolution can't be zero.\n");
		return -EINVAL;
	}

	if (ctx->irq > 0) {
		ret = devm_request_irq(dev, ctx->irq, pulse_handler, 0,
				       pdev->name, ctx);
		if (ret) {
			dev_err(dev, "Failed to request interrupt: %d\n", ret);
			return ret;
		}
		ctx->sample_start = ktime_get();
		mod_timer(&ctx->rpm_timer, jiffies + HZ);
	}

	hwmon = devm_hwmon_device_register_with_groups(dev, "pwmfan",
						       ctx, pwm_fan_groups);
	if (IS_ERR(hwmon)) {
		dev_err(dev, "Failed to register hwmon device\n");
		return PTR_ERR(hwmon);
	}

	ret = pwm_fan_of_get_cooling_data(dev, ctx);
	if (ret)
		return ret;

	ctx->pwm_fan_state = ctx->pwm_fan_max_state;
	if (IS_ENABLED(CONFIG_THERMAL)) {
		cdev = devm_thermal_of_cooling_device_register(dev,
			dev->of_node, "pwm-fan", ctx, &pwm_fan_cooling_ops);
		if (IS_ERR(cdev)) {
			ret = PTR_ERR(cdev);
			dev_err(dev,
				"Failed to register pwm-fan as cooling device: %d\n",
				ret);
			return ret;
		}
		ctx->cdev = cdev;
		thermal_cdev_update(cdev);
	}

	return 0;
}