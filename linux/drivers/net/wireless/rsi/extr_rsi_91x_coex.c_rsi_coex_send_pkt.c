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
typedef  int /*<<< orphan*/  u8 ;
struct skb_info {int flags; } ;
struct sk_buff {scalar_t__ priority; } ;
struct rsi_common {int /*<<< orphan*/  priv; scalar_t__ iface_down; scalar_t__ coex_cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
struct rsi_coex_ctrl_block {TYPE_1__ coex_tx_thread; int /*<<< orphan*/ * coex_tx_qs; } ;
typedef  enum rsi_coex_queues { ____Placeholder_rsi_coex_queues } rsi_coex_queues ;
struct TYPE_4__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ERR_ZONE ; 
 TYPE_2__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int INTERNAL_MGMT_PKT ; 
 scalar_t__ MGMT_SOFT_Q ; 
 int RSI_COEX_Q_COMMON ; 
 int RSI_COEX_Q_INVALID ; 
 int RSI_COEX_Q_WLAN ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_indicate_tx_status (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int rsi_map_coex_q (int /*<<< orphan*/ ) ; 
 int rsi_send_data_pkt (struct rsi_common*,struct sk_buff*) ; 
 int rsi_send_mgmt_pkt (struct rsi_common*,struct sk_buff*) ; 
 int /*<<< orphan*/  rsi_set_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int rsi_coex_send_pkt(void *priv, struct sk_buff *skb, u8 hal_queue)
{
	struct rsi_common *common = (struct rsi_common *)priv;
	struct rsi_coex_ctrl_block *coex_cb =
		(struct rsi_coex_ctrl_block *)common->coex_cb;
	struct skb_info *tx_params = NULL;
	enum rsi_coex_queues coex_q;
	int status;

	coex_q = rsi_map_coex_q(hal_queue);
	if (coex_q == RSI_COEX_Q_INVALID) {
		rsi_dbg(ERR_ZONE, "Invalid coex queue\n");
		return -EINVAL;
	}
	if (coex_q != RSI_COEX_Q_COMMON &&
	    coex_q != RSI_COEX_Q_WLAN) {
		skb_queue_tail(&coex_cb->coex_tx_qs[coex_q], skb);
		rsi_set_event(&coex_cb->coex_tx_thread.event);
		return 0;
	}
	if (common->iface_down) {
		tx_params =
			(struct skb_info *)&IEEE80211_SKB_CB(skb)->driver_data;

		if (!(tx_params->flags & INTERNAL_MGMT_PKT)) {
			rsi_indicate_tx_status(common->priv, skb, -EINVAL);
			return 0;
		}
	}

	/* Send packet to hal */
	if (skb->priority == MGMT_SOFT_Q)
		status = rsi_send_mgmt_pkt(common, skb);
	else
		status = rsi_send_data_pkt(common, skb);

	return status;
}