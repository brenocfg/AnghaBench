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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct rtw_dev {int dummy; } ;
struct rtw_coex_info_req {int /*<<< orphan*/  op_code; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MP_INFO_OP_SCAN_TYPE ; 
 int /*<<< orphan*/  GET_COEX_RESP_BT_SCAN_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/ * get_payload_from_coex_resp (struct sk_buff*) ; 
 struct sk_buff* rtw_coex_info_request (struct rtw_dev*,struct rtw_coex_info_req*) ; 

__attribute__((used)) static bool rtw_coex_get_bt_scan_type(struct rtw_dev *rtwdev, u8 *scan_type)
{
	struct rtw_coex_info_req req = {0};
	struct sk_buff *skb;
	u8 *payload;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_SCAN_TYPE;
	skb = rtw_coex_info_request(rtwdev, &req);
	if (!skb)
		goto out;

	payload = get_payload_from_coex_resp(skb);
	*scan_type = GET_COEX_RESP_BT_SCAN_TYPE(payload);
	dev_kfree_skb_any(skb);
	ret = true;

out:
	return ret;
}