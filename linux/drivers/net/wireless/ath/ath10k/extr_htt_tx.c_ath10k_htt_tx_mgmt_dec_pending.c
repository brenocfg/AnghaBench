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
struct ath10k_htt {int /*<<< orphan*/  num_pending_mgmt_tx; TYPE_2__* ar; int /*<<< orphan*/  tx_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_probe_resp_desc_thres; } ;
struct TYPE_4__ {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ath10k_htt_tx_mgmt_dec_pending(struct ath10k_htt *htt)
{
	lockdep_assert_held(&htt->tx_lock);

	if (!htt->ar->hw_params.max_probe_resp_desc_thres)
		return;

	htt->num_pending_mgmt_tx--;
}