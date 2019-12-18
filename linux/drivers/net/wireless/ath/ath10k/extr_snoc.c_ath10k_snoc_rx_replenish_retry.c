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
struct ath10k_snoc {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_snoc* ar_snoc ; 
 int /*<<< orphan*/  ath10k_snoc_rx_post (struct ath10k*) ; 
 struct ath10k_snoc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_post_retry ; 

__attribute__((used)) static void ath10k_snoc_rx_replenish_retry(struct timer_list *t)
{
	struct ath10k_snoc *ar_snoc = from_timer(ar_snoc, t, rx_post_retry);
	struct ath10k *ar = ar_snoc->ar;

	ath10k_snoc_rx_post(ar);
}