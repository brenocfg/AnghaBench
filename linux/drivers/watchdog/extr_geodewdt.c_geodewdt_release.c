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
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WDT_FLAGS_OPEN ; 
 int /*<<< orphan*/  WDT_FLAGS_ORPHAN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geodewdt_disable () ; 
 int /*<<< orphan*/  geodewdt_ping () ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ safe_close ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_flags ; 

__attribute__((used)) static int geodewdt_release(struct inode *inode, struct file *file)
{
	if (safe_close) {
		geodewdt_disable();
		module_put(THIS_MODULE);
	} else {
		pr_crit("Unexpected close - watchdog is not stopping\n");
		geodewdt_ping();

		set_bit(WDT_FLAGS_ORPHAN, &wdt_flags);
	}

	clear_bit(WDT_FLAGS_OPEN, &wdt_flags);
	safe_close = 0;
	return 0;
}