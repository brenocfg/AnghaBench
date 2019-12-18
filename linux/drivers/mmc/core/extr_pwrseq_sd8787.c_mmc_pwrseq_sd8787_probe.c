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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct mmc_pwrseq_sd8787 {TYPE_1__ pwrseq; void* reset_gpio; void* pwrdn_gpio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mmc_pwrseq_sd8787* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int mmc_pwrseq_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_pwrseq_sd8787_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_pwrseq_sd8787*) ; 

__attribute__((used)) static int mmc_pwrseq_sd8787_probe(struct platform_device *pdev)
{
	struct mmc_pwrseq_sd8787 *pwrseq;
	struct device *dev = &pdev->dev;

	pwrseq = devm_kzalloc(dev, sizeof(*pwrseq), GFP_KERNEL);
	if (!pwrseq)
		return -ENOMEM;

	pwrseq->pwrdn_gpio = devm_gpiod_get(dev, "powerdown", GPIOD_OUT_LOW);
	if (IS_ERR(pwrseq->pwrdn_gpio))
		return PTR_ERR(pwrseq->pwrdn_gpio);

	pwrseq->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(pwrseq->reset_gpio))
		return PTR_ERR(pwrseq->reset_gpio);

	pwrseq->pwrseq.dev = dev;
	pwrseq->pwrseq.ops = &mmc_pwrseq_sd8787_ops;
	pwrseq->pwrseq.owner = THIS_MODULE;
	platform_set_drvdata(pdev, pwrseq);

	return mmc_pwrseq_register(&pwrseq->pwrseq);
}