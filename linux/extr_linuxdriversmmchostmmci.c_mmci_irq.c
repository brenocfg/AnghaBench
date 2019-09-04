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
typedef  int u32 ;
struct mmci_host {int mask1_reg; int /*<<< orphan*/  lock; TYPE_1__* variant; scalar_t__ busy_status; int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  mmc; scalar_t__ base; scalar_t__ singleirq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int busy_detect_mask; int busy_detect_flag; scalar_t__ busy_detect; scalar_t__ reversed_irq_handling; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MCI_IRQ1MASK ; 
 scalar_t__ MMCICLEAR ; 
 scalar_t__ MMCIMASK0 ; 
 scalar_t__ MMCISTATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmci_cmd_irq (struct mmci_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmci_data_irq (struct mmci_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmci_pio_irq (int,void*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mmci_irq(int irq, void *dev_id)
{
	struct mmci_host *host = dev_id;
	u32 status;
	int ret = 0;

	spin_lock(&host->lock);

	do {
		status = readl(host->base + MMCISTATUS);

		if (host->singleirq) {
			if (status & host->mask1_reg)
				mmci_pio_irq(irq, dev_id);

			status &= ~MCI_IRQ1MASK;
		}

		/*
		 * We intentionally clear the MCI_ST_CARDBUSY IRQ (if it's
		 * enabled) in mmci_cmd_irq() function where ST Micro busy
		 * detection variant is handled. Considering the HW seems to be
		 * triggering the IRQ on both edges while monitoring DAT0 for
		 * busy completion and that same status bit is used to monitor
		 * start and end of busy detection, special care must be taken
		 * to make sure that both start and end interrupts are always
		 * cleared one after the other.
		 */
		status &= readl(host->base + MMCIMASK0);
		if (host->variant->busy_detect)
			writel(status & ~host->variant->busy_detect_mask,
			       host->base + MMCICLEAR);
		else
			writel(status, host->base + MMCICLEAR);

		dev_dbg(mmc_dev(host->mmc), "irq0 (data+cmd) %08x\n", status);

		if (host->variant->reversed_irq_handling) {
			mmci_data_irq(host, host->data, status);
			mmci_cmd_irq(host, host->cmd, status);
		} else {
			mmci_cmd_irq(host, host->cmd, status);
			mmci_data_irq(host, host->data, status);
		}

		/*
		 * Don't poll for busy completion in irq context.
		 */
		if (host->variant->busy_detect && host->busy_status)
			status &= ~host->variant->busy_detect_flag;

		ret = 1;
	} while (status);

	spin_unlock(&host->lock);

	return IRQ_RETVAL(ret);
}