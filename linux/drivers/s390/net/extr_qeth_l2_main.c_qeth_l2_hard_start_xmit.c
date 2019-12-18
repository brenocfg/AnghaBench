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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_3__ {struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {TYPE_1__ qdio; } ;
struct net_device {struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  pkt_len; } ;

/* Variables and functions */
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 scalar_t__ IS_OSN (struct qeth_card*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_2__* qdisc_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_get_ip_version (struct sk_buff*) ; 
 size_t qeth_iqd_translate_txq (struct net_device*,size_t) ; 
 int /*<<< orphan*/  qeth_l2_fill_header ; 
 int qeth_l2_xmit_osn (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*) ; 
 int qeth_xmit (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_dropped ; 

__attribute__((used)) static netdev_tx_t qeth_l2_hard_start_xmit(struct sk_buff *skb,
					   struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	u16 txq = skb_get_queue_mapping(skb);
	struct qeth_qdio_out_q *queue;
	int rc;

	if (!skb_is_gso(skb))
		qdisc_skb_cb(skb)->pkt_len = skb->len;
	if (IS_IQD(card))
		txq = qeth_iqd_translate_txq(dev, txq);
	queue = card->qdio.out_qs[txq];

	if (IS_OSN(card))
		rc = qeth_l2_xmit_osn(card, skb, queue);
	else
		rc = qeth_xmit(card, skb, queue, qeth_get_ip_version(skb),
			       qeth_l2_fill_header);

	if (!rc)
		return NETDEV_TX_OK;

	QETH_TXQ_STAT_INC(queue, tx_dropped);
	kfree_skb(skb);
	return NETDEV_TX_OK;
}