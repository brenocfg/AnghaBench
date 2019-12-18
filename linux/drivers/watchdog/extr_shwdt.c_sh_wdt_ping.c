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
typedef  int /*<<< orphan*/  u8 ;
struct timer_list {int dummy; } ;
struct sh_wdt {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WTCSR_IOVF ; 
 int /*<<< orphan*/  clock_division_ratio ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct sh_wdt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_heartbeat ; 
 int /*<<< orphan*/  next_ping_period (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_wdt_read_csr () ; 
 int /*<<< orphan*/  sh_wdt_write_cnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_wdt_write_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 struct sh_wdt* wdt ; 

__attribute__((used)) static void sh_wdt_ping(struct timer_list *t)
{
	struct sh_wdt *wdt = from_timer(wdt, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&wdt->lock, flags);
	if (time_before(jiffies, next_heartbeat)) {
		u8 csr;

		csr = sh_wdt_read_csr();
		csr &= ~WTCSR_IOVF;
		sh_wdt_write_csr(csr);

		sh_wdt_write_cnt(0);

		mod_timer(&wdt->timer, next_ping_period(clock_division_ratio));
	} else
		dev_warn(wdt->dev, "Heartbeat lost! Will not ping "
		         "the watchdog\n");
	spin_unlock_irqrestore(&wdt->lock, flags);
}