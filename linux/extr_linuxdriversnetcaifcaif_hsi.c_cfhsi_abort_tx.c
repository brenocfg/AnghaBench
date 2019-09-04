#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ inactivity_timeout; } ;
struct cfhsi {int /*<<< orphan*/  lock; TYPE_3__ cfg; int /*<<< orphan*/  inactivity_timer; int /*<<< orphan*/  bits; int /*<<< orphan*/  tx_state; TYPE_2__* ndev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFHSI_SHUTDOWN ; 
 int /*<<< orphan*/  CFHSI_TX_STATE_IDLE ; 
 struct sk_buff* cfhsi_dequeue (struct cfhsi*) ; 
 int /*<<< orphan*/  cfhsi_update_aggregation_stats (struct cfhsi*,struct sk_buff*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfhsi_abort_tx(struct cfhsi *cfhsi)
{
	struct sk_buff *skb;

	for (;;) {
		spin_lock_bh(&cfhsi->lock);
		skb = cfhsi_dequeue(cfhsi);
		if (!skb)
			break;

		cfhsi->ndev->stats.tx_errors++;
		cfhsi->ndev->stats.tx_dropped++;
		cfhsi_update_aggregation_stats(cfhsi, skb, -1);
		spin_unlock_bh(&cfhsi->lock);
		kfree_skb(skb);
	}
	cfhsi->tx_state = CFHSI_TX_STATE_IDLE;
	if (!test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		mod_timer(&cfhsi->inactivity_timer,
			jiffies + cfhsi->cfg.inactivity_timeout);
	spin_unlock_bh(&cfhsi->lock);
}