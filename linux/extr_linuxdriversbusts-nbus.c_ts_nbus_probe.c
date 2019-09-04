#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ts_nbus {struct pwm_device* pwm; int /*<<< orphan*/  lock; } ;
struct pwm_device {int dummy; } ;
struct pwm_args {int /*<<< orphan*/  period; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pwm_device*) ; 
 int PTR_ERR (struct pwm_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ts_nbus*) ; 
 struct ts_nbus* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct pwm_device* devm_pwm_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  pwm_apply_args (struct pwm_device*) ; 
 int pwm_config (struct pwm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_enable (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_get_args (struct pwm_device*,struct pwm_args*) ; 
 int ts_nbus_init_pdata (struct platform_device*,struct ts_nbus*) ; 

__attribute__((used)) static int ts_nbus_probe(struct platform_device *pdev)
{
	struct pwm_device *pwm;
	struct pwm_args pargs;
	struct device *dev = &pdev->dev;
	struct ts_nbus *ts_nbus;
	int ret;

	ts_nbus = devm_kzalloc(dev, sizeof(*ts_nbus), GFP_KERNEL);
	if (!ts_nbus)
		return -ENOMEM;

	mutex_init(&ts_nbus->lock);

	ret = ts_nbus_init_pdata(pdev, ts_nbus);
	if (ret < 0)
		return ret;

	pwm = devm_pwm_get(dev, NULL);
	if (IS_ERR(pwm)) {
		ret = PTR_ERR(pwm);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "unable to request PWM\n");
		return ret;
	}

	pwm_get_args(pwm, &pargs);
	if (!pargs.period) {
		dev_err(&pdev->dev, "invalid PWM period\n");
		return -EINVAL;
	}

	/*
	 * FIXME: pwm_apply_args() should be removed when switching to
	 * the atomic PWM API.
	 */
	pwm_apply_args(pwm);
	ret = pwm_config(pwm, pargs.period, pargs.period);
	if (ret < 0)
		return ret;

	/*
	 * we can now start the FPGA and populate the peripherals.
	 */
	pwm_enable(pwm);
	ts_nbus->pwm = pwm;

	/*
	 * let the child nodes retrieve this instance of the ts-nbus.
	 */
	dev_set_drvdata(dev, ts_nbus);

	ret = of_platform_populate(dev->of_node, NULL, NULL, dev);
	if (ret < 0)
		return ret;

	dev_info(dev, "initialized\n");

	return 0;
}