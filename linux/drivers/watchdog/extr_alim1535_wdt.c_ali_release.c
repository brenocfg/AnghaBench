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
 int ali_expect_release ; 
 int /*<<< orphan*/  ali_is_open ; 
 int /*<<< orphan*/  ali_keepalive () ; 
 int /*<<< orphan*/  ali_stop () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static int ali_release(struct inode *inode, struct file *file)
{
	/*
	 *      Shut off the timer.
	 */
	if (ali_expect_release == 42)
		ali_stop();
	else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		ali_keepalive();
	}
	clear_bit(0, &ali_is_open);
	ali_expect_release = 0;
	return 0;
}