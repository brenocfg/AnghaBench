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
 int harddog_in_fd ; 
 int harddog_out_fd ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_watchdog (int,int) ; 
 scalar_t__ timer_alive ; 

__attribute__((used)) static int harddog_release(struct inode *inode, struct file *file)
{
	/*
	 *	Shut off the timer.
	 */

	spin_lock(&lock);

	stop_watchdog(harddog_in_fd, harddog_out_fd);
	harddog_in_fd = -1;
	harddog_out_fd = -1;

	timer_alive=0;
	spin_unlock(&lock);

	return 0;
}