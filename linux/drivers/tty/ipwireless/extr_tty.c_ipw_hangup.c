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
struct tty_struct {struct ipw_tty* driver_data; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct ipw_tty {int /*<<< orphan*/  ipw_tty_mutex; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_ipw_close (struct ipw_tty*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw_hangup(struct tty_struct *linux_tty)
{
	struct ipw_tty *tty = linux_tty->driver_data;

	if (!tty)
		return;

	mutex_lock(&tty->ipw_tty_mutex);
	if (tty->port.count == 0) {
		mutex_unlock(&tty->ipw_tty_mutex);
		return;
	}

	do_ipw_close(tty);

	mutex_unlock(&tty->ipw_tty_mutex);
}