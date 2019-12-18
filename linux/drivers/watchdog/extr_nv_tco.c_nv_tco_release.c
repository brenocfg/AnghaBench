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
 int tco_expect_close ; 
 int /*<<< orphan*/  tco_timer_keepalive () ; 
 int /*<<< orphan*/  tco_timer_stop () ; 
 int /*<<< orphan*/  timer_alive ; 

__attribute__((used)) static int nv_tco_release(struct inode *inode, struct file *file)
{
	/* Shut off the timer */
	if (tco_expect_close == 42) {
		tco_timer_stop();
	} else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		tco_timer_keepalive();
	}
	clear_bit(0, &timer_alive);
	tco_expect_close = 0;
	return 0;
}