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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; struct device* dev; int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct mmc_pwrseq_emmc {TYPE_2__ pwrseq; TYPE_1__ reset_nb; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mmc_pwrseq_emmc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_pwrseq_emmc_ops ; 
 int /*<<< orphan*/  mmc_pwrseq_emmc_reset_nb ; 
 int mmc_pwrseq_register (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_pwrseq_emmc*) ; 
 int /*<<< orphan*/  register_restart_handler (TYPE_1__*) ; 

__attribute__((used)) static int mmc_pwrseq_emmc_probe(struct platform_device *pdev)
{
	struct mmc_pwrseq_emmc *pwrseq;
	struct device *dev = &pdev->dev;

	pwrseq = devm_kzalloc(dev, sizeof(*pwrseq), GFP_KERNEL);
	if (!pwrseq)
		return -ENOMEM;

	pwrseq->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(pwrseq->reset_gpio))
		return PTR_ERR(pwrseq->reset_gpio);

	if (!gpiod_cansleep(pwrseq->reset_gpio)) {
		/*
		 * register reset handler to ensure emmc reset also from
		 * emergency_reboot(), priority 255 is the highest priority
		 * so it will be executed before any system reboot handler.
		 */
		pwrseq->reset_nb.notifier_call = mmc_pwrseq_emmc_reset_nb;
		pwrseq->reset_nb.priority = 255;
		register_restart_handler(&pwrseq->reset_nb);
	} else {
		dev_notice(dev, "EMMC reset pin tied to a sleepy GPIO driver; reset on emergency-reboot disabled\n");
	}

	pwrseq->pwrseq.ops = &mmc_pwrseq_emmc_ops;
	pwrseq->pwrseq.dev = dev;
	pwrseq->pwrseq.owner = THIS_MODULE;
	platform_set_drvdata(pdev, pwrseq);

	return mmc_pwrseq_register(&pwrseq->pwrseq);
}