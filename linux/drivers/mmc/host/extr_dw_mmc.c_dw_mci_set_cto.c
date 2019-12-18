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
typedef  unsigned int u64 ;
struct dw_mci {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  cto_timer; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  bus_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKDIV ; 
 unsigned int DIV_ROUND_UP_ULL (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_CMD_COMPLETE ; 
 scalar_t__ MSEC_PER_SEC ; 
 int /*<<< orphan*/  TMOUT ; 
 scalar_t__ jiffies ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dw_mci_set_cto(struct dw_mci *host)
{
	unsigned int cto_clks;
	unsigned int cto_div;
	unsigned int cto_ms;
	unsigned long irqflags;

	cto_clks = mci_readl(host, TMOUT) & 0xff;
	cto_div = (mci_readl(host, CLKDIV) & 0xff) * 2;
	if (cto_div == 0)
		cto_div = 1;

	cto_ms = DIV_ROUND_UP_ULL((u64)MSEC_PER_SEC * cto_clks * cto_div,
				  host->bus_hz);

	/* add a bit spare time */
	cto_ms += 10;

	/*
	 * The durations we're working with are fairly short so we have to be
	 * extra careful about synchronization here.  Specifically in hardware a
	 * command timeout is _at most_ 5.1 ms, so that means we expect an
	 * interrupt (either command done or timeout) to come rather quickly
	 * after the mci_writel.  ...but just in case we have a long interrupt
	 * latency let's add a bit of paranoia.
	 *
	 * In general we'll assume that at least an interrupt will be asserted
	 * in hardware by the time the cto_timer runs.  ...and if it hasn't
	 * been asserted in hardware by that time then we'll assume it'll never
	 * come.
	 */
	spin_lock_irqsave(&host->irq_lock, irqflags);
	if (!test_bit(EVENT_CMD_COMPLETE, &host->pending_events))
		mod_timer(&host->cto_timer,
			jiffies + msecs_to_jiffies(cto_ms) + 1);
	spin_unlock_irqrestore(&host->irq_lock, irqflags);
}