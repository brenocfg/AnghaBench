#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct sk_buff {int priority; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {scalar_t__ low_addr; scalar_t__ high_addr; } ;
struct TYPE_7__ {void* low_addr; void* high_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifidx; void* request_id; int /*<<< orphan*/  msgtype; } ;
struct msgbuf_tx_msghdr {int flags; int seg_cnt; TYPE_4__ metadata_buf_addr; scalar_t__ metadata_buf_len; TYPE_3__ data_buf_addr; int /*<<< orphan*/  data_len; int /*<<< orphan*/  txhdr; TYPE_2__ msg; } ;
struct brcmf_pub {TYPE_1__* bus_if; } ;
struct brcmf_msgbuf {int /*<<< orphan*/  tx_pktids; struct brcmf_pub* drvr; struct brcmf_commonring** flowrings; struct brcmf_flowring* flow; } ;
struct brcmf_flowring {int dummy; } ;
struct brcmf_commonring {int /*<<< orphan*/  outstanding_tx; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRCMF_MSGBUF_PKT_FLAGS_FRAME_802_3 ; 
 int BRCMF_MSGBUF_PKT_FLAGS_PRIO_SHIFT ; 
 scalar_t__ BRCMF_MSGBUF_TX_FLUSH_CNT1 ; 
 scalar_t__ BRCMF_MSGBUF_TX_FLUSH_CNT2 ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  MSGBUF_TYPE_TX_POST ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_commonring_lock (struct brcmf_commonring*) ; 
 void* brcmf_commonring_reserve_for_write (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_commonring_unlock (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_commonring_write_available (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_commonring_write_complete (struct brcmf_commonring*) ; 
 struct sk_buff* brcmf_flowring_dequeue (struct brcmf_flowring*,size_t) ; 
 int /*<<< orphan*/  brcmf_flowring_ifidx_get (struct brcmf_flowring*,size_t) ; 
 scalar_t__ brcmf_flowring_qlen (struct brcmf_flowring*,size_t) ; 
 int /*<<< orphan*/  brcmf_flowring_reinsert (struct brcmf_flowring*,size_t,struct sk_buff*) ; 
 scalar_t__ brcmf_msgbuf_alloc_pktid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_get_pktid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 

__attribute__((used)) static void brcmf_msgbuf_txflow(struct brcmf_msgbuf *msgbuf, u16 flowid)
{
	struct brcmf_flowring *flow = msgbuf->flow;
	struct brcmf_pub *drvr = msgbuf->drvr;
	struct brcmf_commonring *commonring;
	void *ret_ptr;
	u32 count;
	struct sk_buff *skb;
	dma_addr_t physaddr;
	u32 pktid;
	struct msgbuf_tx_msghdr *tx_msghdr;
	u64 address;

	commonring = msgbuf->flowrings[flowid];
	if (!brcmf_commonring_write_available(commonring))
		return;

	brcmf_commonring_lock(commonring);

	count = BRCMF_MSGBUF_TX_FLUSH_CNT2 - BRCMF_MSGBUF_TX_FLUSH_CNT1;
	while (brcmf_flowring_qlen(flow, flowid)) {
		skb = brcmf_flowring_dequeue(flow, flowid);
		if (skb == NULL) {
			bphy_err(drvr, "No SKB, but qlen %d\n",
				 brcmf_flowring_qlen(flow, flowid));
			break;
		}
		skb_orphan(skb);
		if (brcmf_msgbuf_alloc_pktid(msgbuf->drvr->bus_if->dev,
					     msgbuf->tx_pktids, skb, ETH_HLEN,
					     &physaddr, &pktid)) {
			brcmf_flowring_reinsert(flow, flowid, skb);
			bphy_err(drvr, "No PKTID available !!\n");
			break;
		}
		ret_ptr = brcmf_commonring_reserve_for_write(commonring);
		if (!ret_ptr) {
			brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_if->dev,
					       msgbuf->tx_pktids, pktid);
			brcmf_flowring_reinsert(flow, flowid, skb);
			break;
		}
		count++;

		tx_msghdr = (struct msgbuf_tx_msghdr *)ret_ptr;

		tx_msghdr->msg.msgtype = MSGBUF_TYPE_TX_POST;
		tx_msghdr->msg.request_id = cpu_to_le32(pktid + 1);
		tx_msghdr->msg.ifidx = brcmf_flowring_ifidx_get(flow, flowid);
		tx_msghdr->flags = BRCMF_MSGBUF_PKT_FLAGS_FRAME_802_3;
		tx_msghdr->flags |= (skb->priority & 0x07) <<
				    BRCMF_MSGBUF_PKT_FLAGS_PRIO_SHIFT;
		tx_msghdr->seg_cnt = 1;
		memcpy(tx_msghdr->txhdr, skb->data, ETH_HLEN);
		tx_msghdr->data_len = cpu_to_le16(skb->len - ETH_HLEN);
		address = (u64)physaddr;
		tx_msghdr->data_buf_addr.high_addr = cpu_to_le32(address >> 32);
		tx_msghdr->data_buf_addr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		tx_msghdr->metadata_buf_len = 0;
		tx_msghdr->metadata_buf_addr.high_addr = 0;
		tx_msghdr->metadata_buf_addr.low_addr = 0;
		atomic_inc(&commonring->outstanding_tx);
		if (count >= BRCMF_MSGBUF_TX_FLUSH_CNT2) {
			brcmf_commonring_write_complete(commonring);
			count = 0;
		}
	}
	if (count)
		brcmf_commonring_write_complete(commonring);
	brcmf_commonring_unlock(commonring);
}