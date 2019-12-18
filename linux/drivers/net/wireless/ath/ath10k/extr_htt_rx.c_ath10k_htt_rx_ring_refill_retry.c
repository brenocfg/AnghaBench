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
struct timer_list {int dummy; } ;
struct ath10k_htt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  refill_retry_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_htt_rx_msdu_buff_replenish (struct ath10k_htt*) ; 
 struct ath10k_htt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ath10k_htt* htt ; 
 TYPE_1__ rx_ring ; 

__attribute__((used)) static void ath10k_htt_rx_ring_refill_retry(struct timer_list *t)
{
	struct ath10k_htt *htt = from_timer(htt, t, rx_ring.refill_retry_timer);

	ath10k_htt_rx_msdu_buff_replenish(htt);
}