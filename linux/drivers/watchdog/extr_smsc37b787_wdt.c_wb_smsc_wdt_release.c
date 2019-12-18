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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  timer_enabled ; 
 int /*<<< orphan*/  wb_smsc_wdt_disable () ; 
 int /*<<< orphan*/  wb_smsc_wdt_reset_timer () ; 

__attribute__((used)) static int wb_smsc_wdt_release(struct inode *inode, struct file *file)
{
	/* Shut off the timer. */

	if (expect_close == 42) {
		wb_smsc_wdt_disable();
		pr_info("Watchdog disabled, sleeping again...\n");
	} else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		wb_smsc_wdt_reset_timer();
	}

	clear_bit(0, &timer_enabled);
	expect_close = 0;
	return 0;
}