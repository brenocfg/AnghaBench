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
struct stm32_timers {int /*<<< orphan*/  max_arr; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int of_pwm_n_cells; int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; struct device* dev; int /*<<< orphan*/  of_xlate; } ;
struct stm32_pwm {TYPE_1__ chip; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  max_arr; int /*<<< orphan*/  lock; } ;
struct device {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct stm32_timers* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct stm32_pwm* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_pwm*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int stm32_pwm_apply_breakinputs (struct stm32_pwm*,struct device_node*) ; 
 int /*<<< orphan*/  stm32_pwm_detect_channels (struct stm32_pwm*) ; 
 int /*<<< orphan*/  stm32_pwm_detect_complementary (struct stm32_pwm*) ; 
 int /*<<< orphan*/  stm32pwm_ops ; 

__attribute__((used)) static int stm32_pwm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct stm32_timers *ddata = dev_get_drvdata(pdev->dev.parent);
	struct stm32_pwm *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->lock);
	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->max_arr = ddata->max_arr;
	priv->chip.of_xlate = of_pwm_xlate_with_flags;
	priv->chip.of_pwm_n_cells = 3;

	if (!priv->regmap || !priv->clk)
		return -EINVAL;

	ret = stm32_pwm_apply_breakinputs(priv, np);
	if (ret)
		return ret;

	stm32_pwm_detect_complementary(priv);

	priv->chip.base = -1;
	priv->chip.dev = dev;
	priv->chip.ops = &stm32pwm_ops;
	priv->chip.npwm = stm32_pwm_detect_channels(priv);

	ret = pwmchip_add(&priv->chip);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, priv);

	return 0;
}