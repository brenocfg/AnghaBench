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
typedef  int /*<<< orphan*/  u32 ;
struct timer_list {int dummy; } ;
struct meson_mx_mmc_host {TYPE_1__* cmd; scalar_t__ base; int /*<<< orphan*/  mmc; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 scalar_t__ MESON_MX_SDIO_ARGU ; 
 scalar_t__ MESON_MX_SDIO_IRQC ; 
 int /*<<< orphan*/  MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN ; 
 scalar_t__ MESON_MX_SDIO_IRQS ; 
 int /*<<< orphan*/  cmd_timeout ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_mx_mmc_host* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct meson_mx_mmc_host* host ; 
 int /*<<< orphan*/  meson_mx_mmc_request_done (struct meson_mx_mmc_host*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_mx_mmc_timeout(struct timer_list *t)
{
	struct meson_mx_mmc_host *host = from_timer(host, t, cmd_timeout);
	unsigned long irqflags;
	u32 irqc;

	spin_lock_irqsave(&host->irq_lock, irqflags);

	/* disable the CMD interrupt */
	irqc = readl(host->base + MESON_MX_SDIO_IRQC);
	irqc &= ~MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN;
	writel(irqc, host->base + MESON_MX_SDIO_IRQC);

	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	/*
	 * skip the timeout handling if the interrupt handler already processed
	 * the command.
	 */
	if (!host->cmd)
		return;

	dev_dbg(mmc_dev(host->mmc),
		"Timeout on CMD%u (IRQS = 0x%08x, ARGU = 0x%08x)\n",
		host->cmd->opcode, readl(host->base + MESON_MX_SDIO_IRQS),
		readl(host->base + MESON_MX_SDIO_ARGU));

	host->cmd->error = -ETIMEDOUT;

	meson_mx_mmc_request_done(host);
}