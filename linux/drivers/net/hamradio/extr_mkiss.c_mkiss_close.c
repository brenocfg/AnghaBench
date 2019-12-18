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
struct tty_struct {struct mkiss* disc_data; } ;
struct mkiss {int /*<<< orphan*/  dev; int /*<<< orphan*/ * tty; int /*<<< orphan*/  xbuff; int /*<<< orphan*/  rbuff; int /*<<< orphan*/  dead; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  disc_data_lock ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mkiss_close(struct tty_struct *tty)
{
	struct mkiss *ax;

	write_lock_bh(&disc_data_lock);
	ax = tty->disc_data;
	tty->disc_data = NULL;
	write_unlock_bh(&disc_data_lock);

	if (!ax)
		return;

	/*
	 * We have now ensured that nobody can start using ap from now on, but
	 * we have to wait for all existing users to finish.
	 */
	if (!refcount_dec_and_test(&ax->refcnt))
		wait_for_completion(&ax->dead);
	/*
	 * Halt the transmit queue so that a new transmit cannot scribble
	 * on our buffers
	 */
	netif_stop_queue(ax->dev);

	/* Free all AX25 frame buffers. */
	kfree(ax->rbuff);
	kfree(ax->xbuff);

	ax->tty = NULL;

	unregister_netdev(ax->dev);
}