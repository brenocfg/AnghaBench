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
struct meson_mx_mmc_host {int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MESON_MX_SDIO_IRQS ; 
 int MESON_MX_SDIO_IRQS_CMD_INT ; 
 scalar_t__ MESON_MX_SDIO_SEND ; 
 int /*<<< orphan*/  meson_mx_mmc_process_cmd_irq (struct meson_mx_mmc_host*,int,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t meson_mx_mmc_irq(int irq, void *data)
{
	struct meson_mx_mmc_host *host = (void *) data;
	u32 irqs, send;
	unsigned long irqflags;
	irqreturn_t ret;

	spin_lock_irqsave(&host->irq_lock, irqflags);

	irqs = readl(host->base + MESON_MX_SDIO_IRQS);
	send = readl(host->base + MESON_MX_SDIO_SEND);

	if (irqs & MESON_MX_SDIO_IRQS_CMD_INT)
		ret = meson_mx_mmc_process_cmd_irq(host, irqs, send);
	else
		ret = IRQ_HANDLED;

	/* finally ACK all pending interrupts */
	writel(irqs, host->base + MESON_MX_SDIO_IRQS);

	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	return ret;
}