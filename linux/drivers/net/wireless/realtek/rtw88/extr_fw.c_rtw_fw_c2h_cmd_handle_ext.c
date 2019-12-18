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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct rtw_dev {int dummy; } ;
struct rtw_c2h_cmd {int* payload; } ;

/* Variables and functions */
#define  C2H_CCX_RPT 128 
 struct rtw_c2h_cmd* get_c2h_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_tx_report_handle (struct rtw_dev*,struct sk_buff*) ; 

__attribute__((used)) static void rtw_fw_c2h_cmd_handle_ext(struct rtw_dev *rtwdev,
				      struct sk_buff *skb)
{
	struct rtw_c2h_cmd *c2h;
	u8 sub_cmd_id;

	c2h = get_c2h_from_skb(skb);
	sub_cmd_id = c2h->payload[0];

	switch (sub_cmd_id) {
	case C2H_CCX_RPT:
		rtw_tx_report_handle(rtwdev, skb);
		break;
	default:
		break;
	}
}