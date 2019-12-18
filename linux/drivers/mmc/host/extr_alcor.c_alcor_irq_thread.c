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
typedef  int u32 ;
struct alcor_sdmmc_host {int irq_status_sd; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AU6601_INT_ALL_MASK ; 
 int AU6601_INT_CARD_INSERT ; 
 int AU6601_INT_CARD_REMOVE ; 
 int AU6601_INT_CMD_MASK ; 
 int AU6601_INT_DATA_MASK ; 
 int AU6601_INT_ERROR_MASK ; 
 int AU6601_INT_OVER_CURRENT_ERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  alcor_cd_irq (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_cmd_irq_thread (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_data_irq_thread (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_err_irq (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_unmask_sd_irqs (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t alcor_irq_thread(int irq, void *d)
{
	struct alcor_sdmmc_host *host = d;
	irqreturn_t ret = IRQ_HANDLED;
	u32 intmask, tmp;

	mutex_lock(&host->cmd_mutex);

	intmask = host->irq_status_sd;

	/* some thing bad */
	if (unlikely(!intmask || AU6601_INT_ALL_MASK == intmask)) {
		dev_dbg(host->dev, "unexpected IRQ: 0x%04x\n", intmask);
		ret = IRQ_NONE;
		goto exit;
	}

	tmp = intmask & (AU6601_INT_CMD_MASK | AU6601_INT_DATA_MASK);
	if (tmp) {
		if (tmp & AU6601_INT_ERROR_MASK)
			alcor_err_irq(host, tmp);
		else {
			alcor_cmd_irq_thread(host, tmp);
			alcor_data_irq_thread(host, tmp);
		}
		intmask &= ~(AU6601_INT_CMD_MASK | AU6601_INT_DATA_MASK);
	}

	if (intmask & (AU6601_INT_CARD_INSERT | AU6601_INT_CARD_REMOVE)) {
		alcor_cd_irq(host, intmask);
		intmask &= ~(AU6601_INT_CARD_INSERT | AU6601_INT_CARD_REMOVE);
	}

	if (intmask & AU6601_INT_OVER_CURRENT_ERR) {
		dev_warn(host->dev,
			 "warning: over current detected!\n");
		intmask &= ~AU6601_INT_OVER_CURRENT_ERR;
	}

	if (intmask)
		dev_dbg(host->dev, "got not handled IRQ: 0x%04x\n", intmask);

exit:
	mutex_unlock(&host->cmd_mutex);
	alcor_unmask_sd_irqs(host);
	return ret;
}