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
struct tty_struct {struct syncppp* disc_data; } ;
struct syncppp {int /*<<< orphan*/  tpkt; int /*<<< orphan*/  rqueue; int /*<<< orphan*/  chan; int /*<<< orphan*/  tsk; int /*<<< orphan*/  dead_cmp; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  disc_data_lock ; 
 int /*<<< orphan*/  kfree (struct syncppp*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_unregister_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ppp_sync_close(struct tty_struct *tty)
{
	struct syncppp *ap;

	write_lock_irq(&disc_data_lock);
	ap = tty->disc_data;
	tty->disc_data = NULL;
	write_unlock_irq(&disc_data_lock);
	if (!ap)
		return;

	/*
	 * We have now ensured that nobody can start using ap from now
	 * on, but we have to wait for all existing users to finish.
	 * Note that ppp_unregister_channel ensures that no calls to
	 * our channel ops (i.e. ppp_sync_send/ioctl) are in progress
	 * by the time it returns.
	 */
	if (!refcount_dec_and_test(&ap->refcnt))
		wait_for_completion(&ap->dead_cmp);
	tasklet_kill(&ap->tsk);

	ppp_unregister_channel(&ap->chan);
	skb_queue_purge(&ap->rqueue);
	kfree_skb(ap->tpkt);
	kfree(ap);
}