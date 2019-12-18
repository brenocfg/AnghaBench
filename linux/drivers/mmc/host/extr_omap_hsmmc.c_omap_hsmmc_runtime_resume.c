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
struct omap_hsmmc_host {int flags; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  base; TYPE_1__* mmc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRQ_EN ; 
 int HSMMC_SDIO_IRQ_ENABLED ; 
 int /*<<< orphan*/  IE ; 
 int /*<<< orphan*/  ISE ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAT ; 
 int /*<<< orphan*/  STAT_CLEAR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct omap_hsmmc_host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  omap_hsmmc_context_restore (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int omap_hsmmc_runtime_resume(struct device *dev)
{
	struct omap_hsmmc_host *host;
	unsigned long flags;

	host = dev_get_drvdata(dev);
	omap_hsmmc_context_restore(host);
	dev_dbg(dev, "enabled\n");

	spin_lock_irqsave(&host->irq_lock, flags);
	if ((host->mmc->caps & MMC_CAP_SDIO_IRQ) &&
	    (host->flags & HSMMC_SDIO_IRQ_ENABLED)) {

		pinctrl_pm_select_default_state(host->dev);

		/* irq lost, if pinmux incorrect */
		OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
		OMAP_HSMMC_WRITE(host->base, ISE, CIRQ_EN);
		OMAP_HSMMC_WRITE(host->base, IE, CIRQ_EN);
	} else {
		pinctrl_pm_select_default_state(host->dev);
	}
	spin_unlock_irqrestore(&host->irq_lock, flags);
	return 0;
}