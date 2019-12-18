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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ revision; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  timer; scalar_t__ io_addr; int /*<<< orphan*/  next_heartbeat; } ;

/* Variables and functions */
 scalar_t__ PCWD_REVISION_A ; 
 scalar_t__ WDT_INTERVAL ; 
 int WD_WDRST ; 
 int inb_p (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcwd_timer_ping(struct timer_list *unused)
{
	int wdrst_stat;

	/* If we got a heartbeat pulse within the WDT_INTERVAL
	 * we agree to ping the WDT */
	if (time_before(jiffies, pcwd_private.next_heartbeat)) {
		/* Ping the watchdog */
		spin_lock(&pcwd_private.io_lock);
		if (pcwd_private.revision == PCWD_REVISION_A) {
			/*  Rev A cards are reset by setting the
			    WD_WDRST bit in register 1 */
			wdrst_stat = inb_p(pcwd_private.io_addr);
			wdrst_stat &= 0x0F;
			wdrst_stat |= WD_WDRST;

			outb_p(wdrst_stat, pcwd_private.io_addr + 1);
		} else {
			/* Re-trigger watchdog by writing to port 0 */
			outb_p(0x00, pcwd_private.io_addr);
		}

		/* Re-set the timer interval */
		mod_timer(&pcwd_private.timer, jiffies + WDT_INTERVAL);

		spin_unlock(&pcwd_private.io_lock);
	} else {
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
	}
}