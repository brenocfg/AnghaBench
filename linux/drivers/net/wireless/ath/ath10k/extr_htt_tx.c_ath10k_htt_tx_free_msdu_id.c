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
typedef  int /*<<< orphan*/  u16 ;
struct ath10k_htt {int /*<<< orphan*/  pending_tx; int /*<<< orphan*/  tx_lock; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ath10k_htt_tx_free_msdu_id(struct ath10k_htt *htt, u16 msdu_id)
{
	struct ath10k *ar = htt->ar;

	lockdep_assert_held(&htt->tx_lock);

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx free msdu_id %hu\n", msdu_id);

	idr_remove(&htt->pending_tx, msdu_id);
}