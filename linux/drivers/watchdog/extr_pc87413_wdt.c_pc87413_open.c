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
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  pc87413_refresh () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  timer_enabled ; 

__attribute__((used)) static int pc87413_open(struct inode *inode, struct file *file)
{
	/* /dev/watchdog can only be opened once */

	if (test_and_set_bit(0, &timer_enabled))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	/* Reload and activate timer */
	pc87413_refresh();

	pr_info("Watchdog enabled. Timeout set to %d minute(s).\n", timeout);

	return stream_open(inode, file);
}