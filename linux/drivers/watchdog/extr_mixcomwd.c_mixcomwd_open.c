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
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixcomwd_opened ; 
 int /*<<< orphan*/  mixcomwd_ping () ; 
 int /*<<< orphan*/  mixcomwd_timer ; 
 scalar_t__ mixcomwd_timer_alive ; 
 scalar_t__ nowayout ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mixcomwd_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &mixcomwd_opened))
		return -EBUSY;

	mixcomwd_ping();

	if (nowayout)
		/*
		 * fops_get() code via open() has already done
		 * a try_module_get() so it is safe to do the
		 * __module_get().
		 */
		__module_get(THIS_MODULE);
	else {
		if (mixcomwd_timer_alive) {
			del_timer(&mixcomwd_timer);
			mixcomwd_timer_alive = 0;
		}
	}
	return stream_open(inode, file);
}