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
typedef  int u8 ;
struct watchdog_device {int dummy; } ;
struct sh_wdt {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int RSTCSR_RSTS ; 
 int WTCSR_RSTS ; 
 int WTCSR_TME ; 
 int WTCSR_WT ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int clock_division_ratio ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ next_heartbeat ; 
 int /*<<< orphan*/  next_ping_period (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int sh_wdt_read_csr () ; 
 int sh_wdt_read_rstcsr () ; 
 int /*<<< orphan*/  sh_wdt_write_cnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_wdt_write_csr (int) ; 
 int /*<<< orphan*/  sh_wdt_write_rstcsr (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sh_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int sh_wdt_start(struct watchdog_device *wdt_dev)
{
	struct sh_wdt *wdt = watchdog_get_drvdata(wdt_dev);
	unsigned long flags;
	u8 csr;

	pm_runtime_get_sync(wdt->dev);
	clk_enable(wdt->clk);

	spin_lock_irqsave(&wdt->lock, flags);

	next_heartbeat = jiffies + (heartbeat * HZ);
	mod_timer(&wdt->timer, next_ping_period(clock_division_ratio));

	csr = sh_wdt_read_csr();
	csr |= WTCSR_WT | clock_division_ratio;
	sh_wdt_write_csr(csr);

	sh_wdt_write_cnt(0);

	/*
	 * These processors have a bit of an inconsistent initialization
	 * process.. starting with SH-3, RSTS was moved to WTCSR, and the
	 * RSTCSR register was removed.
	 *
	 * On the SH-2 however, in addition with bits being in different
	 * locations, we must deal with RSTCSR outright..
	 */
	csr = sh_wdt_read_csr();
	csr |= WTCSR_TME;
	csr &= ~WTCSR_RSTS;
	sh_wdt_write_csr(csr);

#ifdef CONFIG_CPU_SH2
	csr = sh_wdt_read_rstcsr();
	csr &= ~RSTCSR_RSTS;
	sh_wdt_write_rstcsr(csr);
#endif
	spin_unlock_irqrestore(&wdt->lock, flags);

	return 0;
}