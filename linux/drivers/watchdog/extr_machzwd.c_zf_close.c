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
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int zf_expect_close ; 
 int /*<<< orphan*/  zf_is_open ; 
 int /*<<< orphan*/  zf_timer ; 
 int /*<<< orphan*/  zf_timer_off () ; 

__attribute__((used)) static int zf_close(struct inode *inode, struct file *file)
{
	if (zf_expect_close == 42)
		zf_timer_off();
	else {
		del_timer(&zf_timer);
		pr_err("device file closed unexpectedly. Will not stop the WDT!\n");
	}
	clear_bit(0, &zf_is_open);
	zf_expect_close = 0;
	return 0;
}