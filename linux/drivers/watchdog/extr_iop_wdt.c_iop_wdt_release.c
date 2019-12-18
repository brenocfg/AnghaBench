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
 int /*<<< orphan*/  WDT_ENABLED ; 
 int /*<<< orphan*/  WDT_IN_USE ; 
 int /*<<< orphan*/  WDT_OK_TO_CLOSE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iop_watchdog_timeout () ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wdt_disable () ; 
 int /*<<< orphan*/  wdt_enable () ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int iop_wdt_release(struct inode *inode, struct file *file)
{
	int state = 1;
	if (test_bit(WDT_OK_TO_CLOSE, &wdt_status))
		if (test_bit(WDT_ENABLED, &wdt_status))
			state = wdt_disable();

	/* if the timer is not disabled reload and notify that we are still
	 * going down
	 */
	if (state != 0) {
		wdt_enable();
		pr_crit("Device closed unexpectedly - reset in %lu seconds\n",
			iop_watchdog_timeout());
	}

	clear_bit(WDT_IN_USE, &wdt_status);
	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	return 0;
}