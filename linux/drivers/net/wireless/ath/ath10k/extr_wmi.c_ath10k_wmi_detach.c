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
struct TYPE_6__ {int /*<<< orphan*/  mgmt_pending_tx; } ;
struct ath10k {scalar_t__ svc_rdy_skb; int /*<<< orphan*/  svc_rdy_work; int /*<<< orphan*/  data_lock; TYPE_3__ wmi; TYPE_2__* running_fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_5__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_MGMT_TX_BY_REF ; 
 int /*<<< orphan*/  ath10k_wmi_mgmt_tx_clean_up_pending ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath10k_wmi_detach(struct ath10k *ar)
{
	if (test_bit(ATH10K_FW_FEATURE_MGMT_TX_BY_REF,
		     ar->running_fw->fw_file.fw_features)) {
		spin_lock_bh(&ar->data_lock);
		idr_for_each(&ar->wmi.mgmt_pending_tx,
			     ath10k_wmi_mgmt_tx_clean_up_pending, ar);
		idr_destroy(&ar->wmi.mgmt_pending_tx);
		spin_unlock_bh(&ar->data_lock);
	}

	cancel_work_sync(&ar->svc_rdy_work);

	if (ar->svc_rdy_skb)
		dev_kfree_skb(ar->svc_rdy_skb);
}