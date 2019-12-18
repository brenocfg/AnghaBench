#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct rtw_tx_pkt_info {scalar_t__ tx_pkt_size; } ;
struct rtw_dev {TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/  pkt_info ;
struct TYPE_2__ {scalar_t__ tx_pkt_desc_sz; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RTW_TX_QUEUE_H2C ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct rtw_tx_pkt_info*,int /*<<< orphan*/ ,int) ; 
 int rtw_pci_xmit (struct rtw_dev*,struct rtw_tx_pkt_info*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int rtw_pci_write_data_h2c(struct rtw_dev *rtwdev, u8 *buf, u32 size)
{
	struct sk_buff *skb;
	struct rtw_tx_pkt_info pkt_info;
	u32 tx_pkt_desc_sz;
	u32 length;

	tx_pkt_desc_sz = rtwdev->chip->tx_pkt_desc_sz;
	length = size + tx_pkt_desc_sz;
	skb = dev_alloc_skb(length);
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, tx_pkt_desc_sz);
	memcpy((u8 *)skb_put(skb, size), buf, size);
	memset(&pkt_info, 0, sizeof(pkt_info));
	pkt_info.tx_pkt_size = size;

	return rtw_pci_xmit(rtwdev, &pkt_info, skb, RTW_TX_QUEUE_H2C);
}