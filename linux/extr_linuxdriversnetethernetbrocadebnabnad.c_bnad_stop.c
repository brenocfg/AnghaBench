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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  enet_comp; } ;
struct TYPE_3__ {int /*<<< orphan*/  enet; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; TYPE_2__ bnad_completions; int /*<<< orphan*/  bna_lock; TYPE_1__ bna; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_HARD_CLEANUP ; 
 int /*<<< orphan*/  bna_enet_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_cb_enet_disabled ; 
 int /*<<< orphan*/  bnad_destroy_rx (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_destroy_tx (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_mbox_irq_sync (struct bnad*) ; 
 int /*<<< orphan*/  bnad_stats_timer_stop (struct bnad*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnad_stop(struct net_device *netdev)
{
	struct bnad *bnad = netdev_priv(netdev);
	unsigned long flags;

	mutex_lock(&bnad->conf_mutex);

	/* Stop the stats timer */
	bnad_stats_timer_stop(bnad);

	init_completion(&bnad->bnad_completions.enet_comp);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_disable(&bnad->bna.enet, BNA_HARD_CLEANUP,
			bnad_cb_enet_disabled);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	wait_for_completion(&bnad->bnad_completions.enet_comp);

	bnad_destroy_tx(bnad, 0);
	bnad_destroy_rx(bnad, 0);

	/* Synchronize mailbox IRQ */
	bnad_mbox_irq_sync(bnad);

	mutex_unlock(&bnad->conf_mutex);

	return 0;
}