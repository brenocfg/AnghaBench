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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct be_wrb_params {int /*<<< orphan*/  features; int /*<<< orphan*/  member_0; } ;
struct be_tx_obj {scalar_t__ pend_wrb_cnt; } ;
struct be_adapter {struct be_tx_obj* tx_obj; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_drv_drops; int /*<<< orphan*/  tx_stops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_WRB_F_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  OS2BMC ; 
 scalar_t__ __netif_subqueue_stopped (struct net_device*,size_t) ; 
 int /*<<< orphan*/  be_get_wrb_params_from_skb (struct be_adapter*,struct sk_buff*,struct be_wrb_params*) ; 
 scalar_t__ be_is_txq_full (struct be_tx_obj*) ; 
 scalar_t__ be_send_pkt_to_bmc (struct be_adapter*,struct sk_buff**) ; 
 size_t be_xmit_enqueue (struct be_adapter*,struct be_tx_obj*,struct sk_buff*,struct be_wrb_params*) ; 
 int /*<<< orphan*/  be_xmit_flush (struct be_adapter*,struct be_tx_obj*) ; 
 struct sk_buff* be_xmit_workarounds (struct be_adapter*,struct sk_buff*,struct be_wrb_params*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_stop_subqueue (struct net_device*,size_t) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 TYPE_1__* tx_stats (struct be_tx_obj*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t be_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	u16 q_idx = skb_get_queue_mapping(skb);
	struct be_tx_obj *txo = &adapter->tx_obj[q_idx];
	struct be_wrb_params wrb_params = { 0 };
	bool flush = !netdev_xmit_more();
	u16 wrb_cnt;

	skb = be_xmit_workarounds(adapter, skb, &wrb_params);
	if (unlikely(!skb))
		goto drop;

	be_get_wrb_params_from_skb(adapter, skb, &wrb_params);

	wrb_cnt = be_xmit_enqueue(adapter, txo, skb, &wrb_params);
	if (unlikely(!wrb_cnt)) {
		dev_kfree_skb_any(skb);
		goto drop;
	}

	/* if os2bmc is enabled and if the pkt is destined to bmc,
	 * enqueue the pkt a 2nd time with mgmt bit set.
	 */
	if (be_send_pkt_to_bmc(adapter, &skb)) {
		BE_WRB_F_SET(wrb_params.features, OS2BMC, 1);
		wrb_cnt = be_xmit_enqueue(adapter, txo, skb, &wrb_params);
		if (unlikely(!wrb_cnt))
			goto drop;
		else
			skb_get(skb);
	}

	if (be_is_txq_full(txo)) {
		netif_stop_subqueue(netdev, q_idx);
		tx_stats(txo)->tx_stops++;
	}

	if (flush || __netif_subqueue_stopped(netdev, q_idx))
		be_xmit_flush(adapter, txo);

	return NETDEV_TX_OK;
drop:
	tx_stats(txo)->tx_drv_drops++;
	/* Flush the already enqueued tx requests */
	if (flush && txo->pend_wrb_cnt)
		be_xmit_flush(adapter, txo);

	return NETDEV_TX_OK;
}