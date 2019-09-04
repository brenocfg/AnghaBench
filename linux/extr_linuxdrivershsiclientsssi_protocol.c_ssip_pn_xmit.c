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
typedef  int /*<<< orphan*/  u16 ;
struct ssi_protocol {scalar_t__ main_state; scalar_t__ txqueue_len; scalar_t__ send_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  txqueue; } ;
struct sk_buff {int len; scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int tx_bytes; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {scalar_t__ tx_queue_len; TYPE_2__ stats; TYPE_1__ dev; } ;
struct hsi_msg {int /*<<< orphan*/  link; int /*<<< orphan*/  complete; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ ACTIVE ; 
 int /*<<< orphan*/  ETH_P_PHONET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ SEND_IDLE ; 
 scalar_t__ SEND_READY ; 
 int SSIP_MIN_PN_HDR ; 
 int /*<<< orphan*/  WAIT4READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 
 int /*<<< orphan*/  hsi_start_tx (struct hsi_client*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_pad (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct hsi_msg* ssip_alloc_data (struct ssi_protocol*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_tx_data_complete ; 
 struct hsi_client* to_hsi_client (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ssip_pn_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct hsi_client *cl = to_hsi_client(dev->dev.parent);
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *msg;

	if ((skb->protocol != htons(ETH_P_PHONET)) ||
					(skb->len < SSIP_MIN_PN_HDR))
		goto drop;
	/* Pad to 32-bits - FIXME: Revisit*/
	if ((skb->len & 3) && skb_pad(skb, 4 - (skb->len & 3)))
		goto inc_dropped;

	/*
	 * Modem sends Phonet messages over SSI with its own endianness.
	 * Assume that modem has the same endianness as we do.
	 */
	if (skb_cow_head(skb, 0))
		goto drop;

	/* length field is exchanged in network byte order */
	((u16 *)skb->data)[2] = htons(((u16 *)skb->data)[2]);

	msg = ssip_alloc_data(ssi, skb, GFP_ATOMIC);
	if (!msg) {
		dev_dbg(&cl->device, "Dropping tx data: No memory\n");
		goto drop;
	}
	msg->complete = ssip_tx_data_complete;

	spin_lock_bh(&ssi->lock);
	if (unlikely(ssi->main_state != ACTIVE)) {
		spin_unlock_bh(&ssi->lock);
		dev_dbg(&cl->device, "Dropping tx data: CMT is OFFLINE\n");
		goto drop2;
	}
	list_add_tail(&msg->link, &ssi->txqueue);
	ssi->txqueue_len++;
	if (dev->tx_queue_len < ssi->txqueue_len) {
		dev_info(&cl->device, "TX queue full %d\n", ssi->txqueue_len);
		netif_stop_queue(dev);
	}
	if (ssi->send_state == SEND_IDLE) {
		ssip_set_txstate(ssi, WAIT4READY);
		spin_unlock_bh(&ssi->lock);
		dev_dbg(&cl->device, "Start TX qlen %d\n", ssi->txqueue_len);
		hsi_start_tx(cl);
	} else if (ssi->send_state == SEND_READY) {
		/* Needed for cmt-speech workaround */
		dev_dbg(&cl->device, "Start TX on SEND READY qlen %d\n",
							ssi->txqueue_len);
		spin_unlock_bh(&ssi->lock);
		schedule_work(&ssi->work);
	} else {
		spin_unlock_bh(&ssi->lock);
	}
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	return 0;
drop2:
	hsi_free_msg(msg);
drop:
	dev_kfree_skb(skb);
inc_dropped:
	dev->stats.tx_dropped++;

	return 0;
}