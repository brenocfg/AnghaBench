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
struct sk_buff {int dummy; } ;
struct rtw_coex {int /*<<< orphan*/  wait; int /*<<< orphan*/  queue; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 scalar_t__ COEX_RESP_ACK_BY_WL_FW ; 
 scalar_t__* get_payload_from_coex_resp (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void rtw_coex_info_response(struct rtw_dev *rtwdev, struct sk_buff *skb)
{
	struct rtw_coex *coex = &rtwdev->coex;
	u8 *payload = get_payload_from_coex_resp(skb);

	if (payload[0] != COEX_RESP_ACK_BY_WL_FW)
		return;

	skb_queue_tail(&coex->queue, skb);
	wake_up(&coex->wait);
}