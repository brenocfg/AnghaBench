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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_6__ {void* low_addr; void* high_addr; } ;
struct TYPE_5__ {void* request_id; int /*<<< orphan*/  msgtype; } ;
struct msgbuf_rx_ioctl_resp_or_event {TYPE_3__ host_buf_addr; int /*<<< orphan*/  host_buf_len; TYPE_2__ msg; } ;
struct brcmf_pub {TYPE_1__* bus_if; } ;
struct brcmf_msgbuf {int /*<<< orphan*/  rx_pktids; struct brcmf_pub* drvr; struct brcmf_commonring** commonrings; } ;
struct brcmf_commonring {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BRCMF_H2D_MSGRING_CONTROL_SUBMIT ; 
 int /*<<< orphan*/  BRCMF_MSGBUF_MAX_PKT_SIZE ; 
 int /*<<< orphan*/  MSGBUF_TYPE_EVENT_BUF_POST ; 
 int /*<<< orphan*/  MSGBUF_TYPE_IOCTLRESP_BUF_POST ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_commonring_len_item (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_commonring_lock (struct brcmf_commonring*) ; 
 void* brcmf_commonring_reserve_for_write_multiple (struct brcmf_commonring*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  brcmf_commonring_unlock (struct brcmf_commonring*) ; 
 int /*<<< orphan*/  brcmf_commonring_write_cancel (struct brcmf_commonring*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_commonring_write_complete (struct brcmf_commonring*) ; 
 scalar_t__ brcmf_msgbuf_alloc_pktid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 struct sk_buff* brcmu_pkt_buf_get_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct msgbuf_rx_ioctl_resp_or_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
brcmf_msgbuf_rxbuf_ctrl_post(struct brcmf_msgbuf *msgbuf, bool event_buf,
			     u32 count)
{
	struct brcmf_pub *drvr = msgbuf->drvr;
	struct brcmf_commonring *commonring;
	void *ret_ptr;
	struct sk_buff *skb;
	u16 alloced;
	u32 pktlen;
	dma_addr_t physaddr;
	struct msgbuf_rx_ioctl_resp_or_event *rx_bufpost;
	u64 address;
	u32 pktid;
	u32 i;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_for_write_multiple(commonring,
							      count,
							      &alloced);
	if (!ret_ptr) {
		bphy_err(drvr, "Failed to reserve space in commonring\n");
		brcmf_commonring_unlock(commonring);
		return 0;
	}

	for (i = 0; i < alloced; i++) {
		rx_bufpost = (struct msgbuf_rx_ioctl_resp_or_event *)ret_ptr;
		memset(rx_bufpost, 0, sizeof(*rx_bufpost));

		skb = brcmu_pkt_buf_get_skb(BRCMF_MSGBUF_MAX_PKT_SIZE);

		if (skb == NULL) {
			bphy_err(drvr, "Failed to alloc SKB\n");
			brcmf_commonring_write_cancel(commonring, alloced - i);
			break;
		}

		pktlen = skb->len;
		if (brcmf_msgbuf_alloc_pktid(msgbuf->drvr->bus_if->dev,
					     msgbuf->rx_pktids, skb, 0,
					     &physaddr, &pktid)) {
			dev_kfree_skb_any(skb);
			bphy_err(drvr, "No PKTID available !!\n");
			brcmf_commonring_write_cancel(commonring, alloced - i);
			break;
		}
		if (event_buf)
			rx_bufpost->msg.msgtype = MSGBUF_TYPE_EVENT_BUF_POST;
		else
			rx_bufpost->msg.msgtype =
				MSGBUF_TYPE_IOCTLRESP_BUF_POST;
		rx_bufpost->msg.request_id = cpu_to_le32(pktid);

		address = (u64)physaddr;
		rx_bufpost->host_buf_len = cpu_to_le16((u16)pktlen);
		rx_bufpost->host_buf_addr.high_addr =
			cpu_to_le32(address >> 32);
		rx_bufpost->host_buf_addr.low_addr =
			cpu_to_le32(address & 0xffffffff);

		ret_ptr += brcmf_commonring_len_item(commonring);
	}

	if (i)
		brcmf_commonring_write_complete(commonring);

	brcmf_commonring_unlock(commonring);

	return i;
}