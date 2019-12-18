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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct lp8788_charger {int /*<<< orphan*/ * pdata; struct lp8788* lp; } ;
struct lp8788 {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * chg_pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct lp8788* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct lp8788_charger* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int lp8788_irq_register (struct platform_device*,struct lp8788_charger*) ; 
 int lp8788_psy_register (struct platform_device*,struct lp8788_charger*) ; 
 int /*<<< orphan*/  lp8788_setup_adc_channel (struct device*,struct lp8788_charger*) ; 
 int lp8788_update_charger_params (struct platform_device*,struct lp8788_charger*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp8788_charger*) ; 

__attribute__((used)) static int lp8788_charger_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct lp8788_charger *pchg;
	struct device *dev = &pdev->dev;
	int ret;

	pchg = devm_kzalloc(dev, sizeof(struct lp8788_charger), GFP_KERNEL);
	if (!pchg)
		return -ENOMEM;

	pchg->lp = lp;
	pchg->pdata = lp->pdata ? lp->pdata->chg_pdata : NULL;
	platform_set_drvdata(pdev, pchg);

	ret = lp8788_update_charger_params(pdev, pchg);
	if (ret)
		return ret;

	lp8788_setup_adc_channel(&pdev->dev, pchg);

	ret = lp8788_psy_register(pdev, pchg);
	if (ret)
		return ret;

	ret = lp8788_irq_register(pdev, pchg);
	if (ret)
		dev_warn(dev, "failed to register charger irq: %d\n", ret);

	return 0;
}