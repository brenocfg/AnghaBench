#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ cb; scalar_t__ len; scalar_t__ data; } ;
struct rtw_dev {int /*<<< orphan*/  c2h_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  c2h_queue; } ;
struct rtw_c2h_cmd {int id; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
#define  C2H_BT_MP_INFO 128 
 int /*<<< orphan*/  RTW_DBG_FW ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_coex_info_response (struct rtw_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void rtw_fw_c2h_cmd_rx_irqsafe(struct rtw_dev *rtwdev, u32 pkt_offset,
			       struct sk_buff *skb)
{
	struct rtw_c2h_cmd *c2h;
	u8 len;

	c2h = (struct rtw_c2h_cmd *)(skb->data + pkt_offset);
	len = skb->len - pkt_offset - 2;
	*((u32 *)skb->cb) = pkt_offset;

	rtw_dbg(rtwdev, RTW_DBG_FW, "recv C2H, id=0x%02x, seq=0x%02x, len=%d\n",
		c2h->id, c2h->seq, len);

	switch (c2h->id) {
	case C2H_BT_MP_INFO:
		rtw_coex_info_response(rtwdev, skb);
		break;
	default:
		/* pass offset for further operation */
		*((u32 *)skb->cb) = pkt_offset;
		skb_queue_tail(&rtwdev->c2h_queue, skb);
		ieee80211_queue_work(rtwdev->hw, &rtwdev->c2h_work);
		break;
	}
}