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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__* cmd; TYPE_2__* ops; } ;
struct ath10k {int /*<<< orphan*/  hw; TYPE_3__ wmi; } ;
struct TYPE_5__ {struct sk_buff* (* gen_mgmt_tx ) (struct ath10k*,struct sk_buff*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  mgmt_tx_cmdid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* stub1 (struct ath10k*,struct sk_buff*) ; 

__attribute__((used)) static inline int
ath10k_wmi_mgmt_tx(struct ath10k *ar, struct sk_buff *msdu)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	struct sk_buff *skb;
	int ret;

	if (!ar->wmi.ops->gen_mgmt_tx)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_mgmt_tx(ar, msdu);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	ret = ath10k_wmi_cmd_send(ar, skb,
				  ar->wmi.cmd->mgmt_tx_cmdid);
	if (ret)
		return ret;

	/* FIXME There's no ACK event for Management Tx. This probably
	 * shouldn't be called here either.
	 */
	info->flags |= IEEE80211_TX_STAT_ACK;
	ieee80211_tx_status_irqsafe(ar->hw, msdu);

	return 0;
}