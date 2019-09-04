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
struct pinctrl {int dummy; } ;
struct omap_hsmmc_host {scalar_t__ wake_irq; TYPE_2__* dev; int /*<<< orphan*/  base; TYPE_1__* pdata; int /*<<< orphan*/  mmc; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {int controller_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  HCTL ; 
 scalar_t__ IS_ERR (struct pinctrl*) ; 
 int IWE ; 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OMAP_HSMMC_SWAKEUP_MISSING ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PINCTRL_STATE_DEFAULT ; 
 int /*<<< orphan*/  PINCTRL_STATE_IDLE ; 
 int PTR_ERR (struct pinctrl*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (TYPE_2__*) ; 
 int dev_pm_set_dedicated_wake_irq (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct pinctrl* devm_pinctrl_get (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_pinctrl_put (struct pinctrl*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct pinctrl* pinctrl_lookup_state (struct pinctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_configure_wake_irq(struct omap_hsmmc_host *host)
{
	int ret;

	/*
	 * For omaps with wake-up path, wakeirq will be irq from pinctrl and
	 * for other omaps, wakeirq will be from GPIO (dat line remuxed to
	 * gpio). wakeirq is needed to detect sdio irq in runtime suspend state
	 * with functional clock disabled.
	 */
	if (!host->dev->of_node || !host->wake_irq)
		return -ENODEV;

	ret = dev_pm_set_dedicated_wake_irq(host->dev, host->wake_irq);
	if (ret) {
		dev_err(mmc_dev(host->mmc), "Unable to request wake IRQ\n");
		goto err;
	}

	/*
	 * Some omaps don't have wake-up path from deeper idle states
	 * and need to remux SDIO DAT1 to GPIO for wake-up from idle.
	 */
	if (host->pdata->controller_flags & OMAP_HSMMC_SWAKEUP_MISSING) {
		struct pinctrl *p = devm_pinctrl_get(host->dev);
		if (IS_ERR(p)) {
			ret = PTR_ERR(p);
			goto err_free_irq;
		}
		if (IS_ERR(pinctrl_lookup_state(p, PINCTRL_STATE_DEFAULT))) {
			dev_info(host->dev, "missing default pinctrl state\n");
			devm_pinctrl_put(p);
			ret = -EINVAL;
			goto err_free_irq;
		}

		if (IS_ERR(pinctrl_lookup_state(p, PINCTRL_STATE_IDLE))) {
			dev_info(host->dev, "missing idle pinctrl state\n");
			devm_pinctrl_put(p);
			ret = -EINVAL;
			goto err_free_irq;
		}
		devm_pinctrl_put(p);
	}

	OMAP_HSMMC_WRITE(host->base, HCTL,
			 OMAP_HSMMC_READ(host->base, HCTL) | IWE);
	return 0;

err_free_irq:
	dev_pm_clear_wake_irq(host->dev);
err:
	dev_warn(host->dev, "no SDIO IRQ support, falling back to polling\n");
	host->wake_irq = 0;
	return ret;
}