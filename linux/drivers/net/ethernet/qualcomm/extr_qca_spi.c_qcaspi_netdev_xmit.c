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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring_full; int /*<<< orphan*/  out_of_mem; } ;
struct TYPE_6__ {size_t tail; int count; struct sk_buff** skb; int /*<<< orphan*/  size; } ;
struct qcaspi {TYPE_2__* spi_thread; TYPE_1__ stats; int /*<<< orphan*/  net_dev; TYPE_3__ txr; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ QCAFRM_FOOTER_LEN ; 
 scalar_t__ QCAFRM_HEADER_LEN ; 
 scalar_t__ QCAFRM_MIN_LEN ; 
 scalar_t__ QCASPI_HW_PKT_LEN ; 
 scalar_t__ TASK_RUNNING ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  qcafrm_create_footer (scalar_t__*) ; 
 int /*<<< orphan*/  qcafrm_create_header (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  qcaspi_tx_ring_has_space (TYPE_3__*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 scalar_t__* skb_push (struct sk_buff*,scalar_t__) ; 
 scalar_t__* skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__* skb_put_zero (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_process (TYPE_2__*) ; 

__attribute__((used)) static netdev_tx_t
qcaspi_netdev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	u32 frame_len;
	u8 *ptmp;
	struct qcaspi *qca = netdev_priv(dev);
	u16 new_tail;
	struct sk_buff *tskb;
	u8 pad_len = 0;

	if (skb->len < QCAFRM_MIN_LEN)
		pad_len = QCAFRM_MIN_LEN - skb->len;

	if (qca->txr.skb[qca->txr.tail]) {
		netdev_warn(qca->net_dev, "queue was unexpectedly full!\n");
		netif_stop_queue(qca->net_dev);
		qca->stats.ring_full++;
		return NETDEV_TX_BUSY;
	}

	if ((skb_headroom(skb) < QCAFRM_HEADER_LEN) ||
	    (skb_tailroom(skb) < QCAFRM_FOOTER_LEN + pad_len)) {
		tskb = skb_copy_expand(skb, QCAFRM_HEADER_LEN,
				       QCAFRM_FOOTER_LEN + pad_len, GFP_ATOMIC);
		if (!tskb) {
			qca->stats.out_of_mem++;
			return NETDEV_TX_BUSY;
		}
		dev_kfree_skb(skb);
		skb = tskb;
	}

	frame_len = skb->len + pad_len;

	ptmp = skb_push(skb, QCAFRM_HEADER_LEN);
	qcafrm_create_header(ptmp, frame_len);

	if (pad_len) {
		ptmp = skb_put_zero(skb, pad_len);
	}

	ptmp = skb_put(skb, QCAFRM_FOOTER_LEN);
	qcafrm_create_footer(ptmp);

	netdev_dbg(qca->net_dev, "Tx-ing packet: Size: 0x%08x\n",
		   skb->len);

	qca->txr.size += skb->len + QCASPI_HW_PKT_LEN;

	new_tail = qca->txr.tail + 1;
	if (new_tail >= qca->txr.count)
		new_tail = 0;

	qca->txr.skb[qca->txr.tail] = skb;
	qca->txr.tail = new_tail;

	if (!qcaspi_tx_ring_has_space(&qca->txr)) {
		netif_stop_queue(qca->net_dev);
		qca->stats.ring_full++;
	}

	netif_trans_update(dev);

	if (qca->spi_thread &&
	    qca->spi_thread->state != TASK_RUNNING)
		wake_up_process(qca->spi_thread);

	return NETDEV_TX_OK;
}