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
 scalar_t__ WDRTAS_MAGIC_CHAR ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ wdrtas_expect_close ; 
 int /*<<< orphan*/  wdrtas_miscdev_open ; 
 int /*<<< orphan*/  wdrtas_timer_keepalive () ; 
 int /*<<< orphan*/  wdrtas_timer_stop () ; 

__attribute__((used)) static int wdrtas_close(struct inode *inode, struct file *file)
{
	/* only stop watchdog, if this was announced using 'V' before */
	if (wdrtas_expect_close == WDRTAS_MAGIC_CHAR)
		wdrtas_timer_stop();
	else {
		pr_warn("got unexpected close. Watchdog not stopped.\n");
		wdrtas_timer_keepalive();
	}

	wdrtas_expect_close = 0;
	atomic_dec(&wdrtas_miscdev_open);
	return 0;
}