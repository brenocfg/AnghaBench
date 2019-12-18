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
 int stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  tco_timer_keepalive () ; 
 int /*<<< orphan*/  tco_timer_start () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_alive ; 

__attribute__((used)) static int nv_tco_open(struct inode *inode, struct file *file)
{
	/* /dev/watchdog can only be opened once */
	if (test_and_set_bit(0, &timer_alive))
		return -EBUSY;

	/* Reload and activate timer */
	tco_timer_keepalive();
	tco_timer_start();
	return stream_open(inode, file);
}