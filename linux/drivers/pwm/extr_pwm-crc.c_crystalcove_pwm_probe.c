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
struct TYPE_4__ {struct device* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int base; int npwm; int /*<<< orphan*/ * ops; TYPE_2__* dev; } ;
struct crystalcove_pwm {TYPE_1__ chip; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  crc_pwm_ops ; 
 struct intel_soc_pmic* dev_get_drvdata (struct device*) ; 
 struct crystalcove_pwm* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct crystalcove_pwm*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int crystalcove_pwm_probe(struct platform_device *pdev)
{
	struct crystalcove_pwm *pwm;
	struct device *dev = pdev->dev.parent;
	struct intel_soc_pmic *pmic = dev_get_drvdata(dev);

	pwm = devm_kzalloc(&pdev->dev, sizeof(*pwm), GFP_KERNEL);
	if (!pwm)
		return -ENOMEM;

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &crc_pwm_ops;
	pwm->chip.base = -1;
	pwm->chip.npwm = 1;

	/* get the PMIC regmap */
	pwm->regmap = pmic->regmap;

	platform_set_drvdata(pdev, pwm);

	return pwmchip_add(&pwm->chip);
}