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
struct tty_struct {int /*<<< orphan*/ * disc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * this_tty ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writelock ; 

__attribute__((used)) static void n_tracesink_close(struct tty_struct *tty)
{
	mutex_lock(&writelock);
	tty_driver_flush_buffer(tty);
	tty_kref_put(this_tty);
	this_tty = NULL;
	tty->disc_data = NULL;
	mutex_unlock(&writelock);
}