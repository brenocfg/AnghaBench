#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; struct tty_struct* link; TYPE_2__* port; int /*<<< orphan*/  driver; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/ * itty; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* shutdown ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_buffer_cancel_work (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_driver_remove_tty (int /*<<< orphan*/ ,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_mutex ; 
 int /*<<< orphan*/  tty_save_termios (struct tty_struct*) ; 

__attribute__((used)) static void release_tty(struct tty_struct *tty, int idx)
{
	/* This should always be true but check for the moment */
	WARN_ON(tty->index != idx);
	WARN_ON(!mutex_is_locked(&tty_mutex));
	if (tty->ops->shutdown)
		tty->ops->shutdown(tty);
	tty_save_termios(tty);
	tty_driver_remove_tty(tty->driver, tty);
	tty->port->itty = NULL;
	if (tty->link)
		tty->link->port->itty = NULL;
	tty_buffer_cancel_work(tty->port);
	if (tty->link)
		tty_buffer_cancel_work(tty->link->port);

	tty_kref_put(tty->link);
	tty_kref_put(tty);
}