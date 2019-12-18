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
typedef  size_t u16 ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  len; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_5__ {struct qeth_qdio_out_q** out_qs; } ;
struct TYPE_4__ {scalar_t__ cq; scalar_t__ sniffer; } ;
struct qeth_card {TYPE_2__ qdio; TYPE_1__ options; } ;
struct net_device {int flags; struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {int /*<<< orphan*/  pkt_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_AF_IUCV ; 
 int IFF_BROADCAST ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int /*<<< orphan*/ ) ; 
 scalar_t__ RTN_BROADCAST ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_3__* qdisc_skb_cb (struct sk_buff*) ; 
 int qeth_get_ip_version (struct sk_buff*) ; 
 size_t qeth_iqd_translate_txq (struct net_device*,size_t) ; 
 int /*<<< orphan*/  qeth_l3_fill_header ; 
 scalar_t__ qeth_l3_get_cast_type (struct sk_buff*) ; 
 int qeth_l3_xmit (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int) ; 
 int qeth_xmit (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int,int /*<<< orphan*/ ) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_dropped ; 

__attribute__((used)) static netdev_tx_t qeth_l3_hard_start_xmit(struct sk_buff *skb,
					   struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	u16 txq = skb_get_queue_mapping(skb);
	int ipv = qeth_get_ip_version(skb);
	struct qeth_qdio_out_q *queue;
	int rc;

	if (!skb_is_gso(skb))
		qdisc_skb_cb(skb)->pkt_len = skb->len;
	if (IS_IQD(card)) {
		queue = card->qdio.out_qs[qeth_iqd_translate_txq(dev, txq)];

		if (card->options.sniffer)
			goto tx_drop;
		if ((card->options.cq != QETH_CQ_ENABLED && !ipv) ||
		    (card->options.cq == QETH_CQ_ENABLED &&
		     skb->protocol != htons(ETH_P_AF_IUCV)))
			goto tx_drop;
	} else {
		queue = card->qdio.out_qs[txq];
	}

	if (!(dev->flags & IFF_BROADCAST) &&
	    qeth_l3_get_cast_type(skb) == RTN_BROADCAST)
		goto tx_drop;

	if (ipv == 4 || IS_IQD(card))
		rc = qeth_l3_xmit(card, skb, queue, ipv);
	else
		rc = qeth_xmit(card, skb, queue, ipv, qeth_l3_fill_header);

	if (!rc)
		return NETDEV_TX_OK;

tx_drop:
	QETH_TXQ_STAT_INC(queue, tx_dropped);
	kfree_skb(skb);
	return NETDEV_TX_OK;
}