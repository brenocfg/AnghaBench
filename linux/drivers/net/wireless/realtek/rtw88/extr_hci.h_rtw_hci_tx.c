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
struct sk_buff {int dummy; } ;
struct rtw_tx_pkt_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtw_dev {TYPE_2__ hci; } ;
struct TYPE_3__ {int (* tx ) (struct rtw_dev*,struct rtw_tx_pkt_info*,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (struct rtw_dev*,struct rtw_tx_pkt_info*,struct sk_buff*) ; 

__attribute__((used)) static inline int rtw_hci_tx(struct rtw_dev *rtwdev,
			     struct rtw_tx_pkt_info *pkt_info,
			     struct sk_buff *skb)
{
	return rtwdev->hci.ops->tx(rtwdev, pkt_info, skb);
}