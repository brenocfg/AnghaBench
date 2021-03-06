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
 scalar_t__ epx_c3_alive ; 
 int /*<<< orphan*/  epx_c3_stop () ; 
 int /*<<< orphan*/  nowayout ; 

__attribute__((used)) static int epx_c3_release(struct inode *inode, struct file *file)
{
	/* Shut off the timer.
	 * Lock it in if it's a module and we defined ...NOWAYOUT */
	if (!nowayout)
		epx_c3_stop();		/* Turn the WDT off */

	epx_c3_alive = 0;

	return 0;
}