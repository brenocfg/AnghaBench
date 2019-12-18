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
struct timer_list {int dummy; } ;
struct bnad {int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  bna; int /*<<< orphan*/  run_flags; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_STATS_TIMER_RUNNING ; 
 int /*<<< orphan*/  bna_hw_stats_get (int /*<<< orphan*/ *) ; 
 struct bnad* bnad ; 
 struct bnad* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stats_timer ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_stats_timeout(struct timer_list *t)
{
	struct bnad *bnad = from_timer(bnad, t, stats_timer);
	unsigned long flags;

	if (!netif_running(bnad->netdev) ||
		!test_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags))
		return;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_hw_stats_get(&bnad->bna);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}