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
 int /*<<< orphan*/  pr_crit (char*) ; 
 int sch311x_wdt_expect_close ; 
 int /*<<< orphan*/  sch311x_wdt_is_open ; 
 int /*<<< orphan*/  sch311x_wdt_keepalive () ; 
 int /*<<< orphan*/  sch311x_wdt_stop () ; 

__attribute__((used)) static int sch311x_wdt_close(struct inode *inode, struct file *file)
{
	if (sch311x_wdt_expect_close == 42) {
		sch311x_wdt_stop();
	} else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		sch311x_wdt_keepalive();
	}
	clear_bit(0, &sch311x_wdt_is_open);
	sch311x_wdt_expect_close = 0;
	return 0;
}