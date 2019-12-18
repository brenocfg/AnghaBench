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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifidx; int /*<<< orphan*/  request_id; } ;
struct msgbuf_rx_event {TYPE_2__ msg; int /*<<< orphan*/  event_data_len; } ;
struct brcmf_pub {TYPE_1__* bus_if; } ;
struct brcmf_msgbuf {struct brcmf_pub* drvr; scalar_t__ rx_dataoffset; int /*<<< orphan*/  rx_pktids; scalar_t__ cur_eventbuf; } ;
struct brcmf_if {int /*<<< orphan*/  drvr; int /*<<< orphan*/  ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fweh_process_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct brcmf_if* brcmf_get_ifp (struct brcmf_pub*,int /*<<< orphan*/ ) ; 
 struct sk_buff* brcmf_msgbuf_get_pktid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_msgbuf_rxbuf_event_post (struct brcmf_msgbuf*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_msgbuf_process_event(struct brcmf_msgbuf *msgbuf, void *buf)
{
	struct brcmf_pub *drvr = msgbuf->drvr;
	struct msgbuf_rx_event *event;
	u32 idx;
	u16 buflen;
	struct sk_buff *skb;
	struct brcmf_if *ifp;

	event = (struct msgbuf_rx_event *)buf;
	idx = le32_to_cpu(event->msg.request_id);
	buflen = le16_to_cpu(event->event_data_len);

	if (msgbuf->cur_eventbuf)
		msgbuf->cur_eventbuf--;
	brcmf_msgbuf_rxbuf_event_post(msgbuf);

	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_if->dev,
				     msgbuf->rx_pktids, idx);
	if (!skb)
		return;

	if (msgbuf->rx_dataoffset)
		skb_pull(skb, msgbuf->rx_dataoffset);

	skb_trim(skb, buflen);

	ifp = brcmf_get_ifp(msgbuf->drvr, event->msg.ifidx);
	if (!ifp || !ifp->ndev) {
		bphy_err(drvr, "Received pkt for invalid ifidx %d\n",
			 event->msg.ifidx);
		goto exit;
	}

	skb->protocol = eth_type_trans(skb, ifp->ndev);

	brcmf_fweh_process_skb(ifp->drvr, skb, 0);

exit:
	brcmu_pkt_buf_free_skb(skb);
}