#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; TYPE_2__* dev; } ;
struct lp3943_pwm {TYPE_1__ chip; struct lp3943* lp3943; int /*<<< orphan*/  pdata; } ;
struct lp3943 {int /*<<< orphan*/  pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LP3943_NUM_PWMS ; 
 struct lp3943* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct lp3943_pwm* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp3943_pwm_ops ; 
 int lp3943_pwm_parse_dt (TYPE_2__*,struct lp3943_pwm*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp3943_pwm*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int lp3943_pwm_probe(struct platform_device *pdev)
{
	struct lp3943 *lp3943 = dev_get_drvdata(pdev->dev.parent);
	struct lp3943_pwm *lp3943_pwm;
	int ret;

	lp3943_pwm = devm_kzalloc(&pdev->dev, sizeof(*lp3943_pwm), GFP_KERNEL);
	if (!lp3943_pwm)
		return -ENOMEM;

	lp3943_pwm->pdata = lp3943->pdata;
	if (!lp3943_pwm->pdata) {
		if (IS_ENABLED(CONFIG_OF))
			ret = lp3943_pwm_parse_dt(&pdev->dev, lp3943_pwm);
		else
			ret = -ENODEV;

		if (ret)
			return ret;
	}

	lp3943_pwm->lp3943 = lp3943;
	lp3943_pwm->chip.dev = &pdev->dev;
	lp3943_pwm->chip.ops = &lp3943_pwm_ops;
	lp3943_pwm->chip.npwm = LP3943_NUM_PWMS;

	platform_set_drvdata(pdev, lp3943_pwm);

	return pwmchip_add(&lp3943_pwm->chip);
}