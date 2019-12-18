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
struct rtw_coex_info_req {int /*<<< orphan*/  para1; int /*<<< orphan*/  op_code; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MP_INFO_OP_LNA_CONSTRAINT ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* rtw_coex_info_request (struct rtw_dev*,struct rtw_coex_info_req*) ; 

__attribute__((used)) static bool rtw_coex_set_lna_constrain_level(struct rtw_dev *rtwdev,
					     u8 lna_constrain_level)
{
	struct rtw_coex_info_req req = {0};
	struct sk_buff *skb;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_LNA_CONSTRAINT;
	req.para1 = lna_constrain_level;
	skb = rtw_coex_info_request(rtwdev, &req);
	if (!skb)
		goto out;

	dev_kfree_skb_any(skb);
	ret = true;

out:
	return ret;
}