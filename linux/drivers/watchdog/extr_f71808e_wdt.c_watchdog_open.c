#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ expect_close; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nowayout ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ watchdog ; 
 int watchdog_start () ; 

__attribute__((used)) static int watchdog_open(struct inode *inode, struct file *file)
{
	int err;

	/* If the watchdog is alive we don't need to start it again */
	if (test_and_set_bit(0, &watchdog.opened))
		return -EBUSY;

	err = watchdog_start();
	if (err) {
		clear_bit(0, &watchdog.opened);
		return err;
	}

	if (nowayout)
		__module_get(THIS_MODULE);

	watchdog.expect_close = 0;
	return stream_open(inode, file);
}