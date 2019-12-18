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
 int /*<<< orphan*/  WDTO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 int /*<<< orphan*/  open_flag ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  sc1200wdt_stop () ; 
 int /*<<< orphan*/  sc1200wdt_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int sc1200wdt_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42) {
		sc1200wdt_stop();
		pr_info("Watchdog disabled\n");
	} else {
		sc1200wdt_write_data(WDTO, timeout);
		pr_crit("Unexpected close!, timeout = %d min(s)\n", timeout);
	}
	clear_bit(0, &open_flag);
	expect_close = 0;

	return 0;
}