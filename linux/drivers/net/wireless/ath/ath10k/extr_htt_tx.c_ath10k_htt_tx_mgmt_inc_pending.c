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
struct ath10k_htt {scalar_t__ num_pending_mgmt_tx; int /*<<< orphan*/  tx_lock; struct ath10k* ar; } ;
struct TYPE_2__ {scalar_t__ max_probe_resp_desc_thres; } ;
struct ath10k {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int ath10k_htt_tx_mgmt_inc_pending(struct ath10k_htt *htt, bool is_mgmt,
				   bool is_presp)
{
	struct ath10k *ar = htt->ar;

	lockdep_assert_held(&htt->tx_lock);

	if (!is_mgmt || !ar->hw_params.max_probe_resp_desc_thres)
		return 0;

	if (is_presp &&
	    ar->hw_params.max_probe_resp_desc_thres < htt->num_pending_mgmt_tx)
		return -EBUSY;

	htt->num_pending_mgmt_tx++;

	return 0;
}