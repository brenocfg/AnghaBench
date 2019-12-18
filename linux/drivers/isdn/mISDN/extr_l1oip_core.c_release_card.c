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
struct l1oip {size_t d_idx; int /*<<< orphan*/  list; TYPE_1__* chan; int /*<<< orphan*/  dev; scalar_t__ registered; scalar_t__ socket_thread; int /*<<< orphan*/  workq; int /*<<< orphan*/  timeout_tl; int /*<<< orphan*/  keep_tl; } ;
struct TYPE_2__ {int /*<<< orphan*/  disorder_skb; struct l1oip* bch; struct l1oip* dch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct l1oip*) ; 
 int /*<<< orphan*/  l1oip_lock ; 
 int /*<<< orphan*/  l1oip_socket_close (struct l1oip*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freebchannel (struct l1oip*) ; 
 int /*<<< orphan*/  mISDN_freedchannel (struct l1oip*) ; 
 int /*<<< orphan*/  mISDN_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_card(struct l1oip *hc)
{
	int	ch;

	if (timer_pending(&hc->keep_tl))
		del_timer(&hc->keep_tl);

	if (timer_pending(&hc->timeout_tl))
		del_timer(&hc->timeout_tl);

	cancel_work_sync(&hc->workq);

	if (hc->socket_thread)
		l1oip_socket_close(hc);

	if (hc->registered && hc->chan[hc->d_idx].dch)
		mISDN_unregister_device(&hc->chan[hc->d_idx].dch->dev);
	for (ch = 0; ch < 128; ch++) {
		if (hc->chan[ch].dch) {
			mISDN_freedchannel(hc->chan[ch].dch);
			kfree(hc->chan[ch].dch);
		}
		if (hc->chan[ch].bch) {
			mISDN_freebchannel(hc->chan[ch].bch);
			kfree(hc->chan[ch].bch);
#ifdef REORDER_DEBUG
			dev_kfree_skb(hc->chan[ch].disorder_skb);
#endif
		}
	}

	spin_lock(&l1oip_lock);
	list_del(&hc->list);
	spin_unlock(&l1oip_lock);

	kfree(hc);
}