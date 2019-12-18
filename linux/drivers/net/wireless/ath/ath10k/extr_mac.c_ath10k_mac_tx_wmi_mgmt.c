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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ath10k {int /*<<< orphan*/  data_lock; int /*<<< orphan*/  wmi_mgmt_tx_work; int /*<<< orphan*/  hw; struct sk_buff_head wmi_mgmt_tx_queue; } ;

/* Variables and functions */
 scalar_t__ ATH10K_MAX_NUM_MGMT_PENDING ; 
 int ENOSPC ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_tx_wmi_mgmt(struct ath10k *ar, struct sk_buff *skb)
{
	struct sk_buff_head *q = &ar->wmi_mgmt_tx_queue;
	int ret = 0;

	spin_lock_bh(&ar->data_lock);

	if (skb_queue_len(q) == ATH10K_MAX_NUM_MGMT_PENDING) {
		ath10k_warn(ar, "wmi mgmt tx queue is full\n");
		ret = -ENOSPC;
		goto unlock;
	}

	__skb_queue_tail(q, skb);
	ieee80211_queue_work(ar->hw, &ar->wmi_mgmt_tx_work);

unlock:
	spin_unlock_bh(&ar->data_lock);

	return ret;
}