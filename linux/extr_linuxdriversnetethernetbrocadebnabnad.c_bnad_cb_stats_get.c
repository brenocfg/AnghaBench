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
struct bnad {int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  run_flags; int /*<<< orphan*/  netdev; } ;
struct bna_stats {int dummy; } ;
typedef  enum bna_cb_status { ____Placeholder_bna_cb_status } bna_cb_status ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_STATS_TIMER_RUNNING ; 
 int /*<<< orphan*/  BNAD_STATS_TIMER_FREQ ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int BNA_CB_SUCCESS ; 
 int /*<<< orphan*/  hw_stats_updates ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bnad_cb_stats_get(struct bnad *bnad, enum bna_cb_status status,
		       struct bna_stats *stats)
{
	if (status == BNA_CB_SUCCESS)
		BNAD_UPDATE_CTR(bnad, hw_stats_updates);

	if (!netif_running(bnad->netdev) ||
		!test_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags))
		return;

	mod_timer(&bnad->stats_timer,
		  jiffies + msecs_to_jiffies(BNAD_STATS_TIMER_FREQ));
}