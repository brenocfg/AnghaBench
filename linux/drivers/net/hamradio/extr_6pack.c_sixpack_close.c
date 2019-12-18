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
struct tty_struct {struct sixpack* disc_data; } ;
struct sixpack {int /*<<< orphan*/  dev; int /*<<< orphan*/  xbuff; int /*<<< orphan*/  rbuff; int /*<<< orphan*/  resync_t; int /*<<< orphan*/  tx_t; int /*<<< orphan*/  dead; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disc_data_lock ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sixpack_close(struct tty_struct *tty)
{
	struct sixpack *sp;

	write_lock_bh(&disc_data_lock);
	sp = tty->disc_data;
	tty->disc_data = NULL;
	write_unlock_bh(&disc_data_lock);
	if (!sp)
		return;

	/*
	 * We have now ensured that nobody can start using ap from now on, but
	 * we have to wait for all existing users to finish.
	 */
	if (!refcount_dec_and_test(&sp->refcnt))
		wait_for_completion(&sp->dead);

	/* We must stop the queue to avoid potentially scribbling
	 * on the free buffers. The sp->dead completion is not sufficient
	 * to protect us from sp->xbuff access.
	 */
	netif_stop_queue(sp->dev);

	del_timer_sync(&sp->tx_t);
	del_timer_sync(&sp->resync_t);

	/* Free all 6pack frame buffers. */
	kfree(sp->rbuff);
	kfree(sp->xbuff);

	unregister_netdev(sp->dev);
}