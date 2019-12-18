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
struct TYPE_2__ {int /*<<< orphan*/  curr_nfc_dep_pni; } ;
struct st21nfca_hci_info {TYPE_1__ dep_info; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST21NFCA_EVT_SEND_DATA ; 
 int /*<<< orphan*/  ST21NFCA_NFCIP1_DEP_RES ; 
 int /*<<< orphan*/  ST21NFCA_NFCIP1_RES ; 
 int /*<<< orphan*/  ST21NFCA_RF_CARD_F_GATE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

int st21nfca_tm_send_dep_res(struct nfc_hci_dev *hdev, struct sk_buff *skb)
{
	int r;
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	*(u8 *)skb_push(skb, 1) = info->dep_info.curr_nfc_dep_pni;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_RES;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_RES;
	*(u8 *)skb_push(skb, 1) = skb->len;

	r = nfc_hci_send_event(hdev, ST21NFCA_RF_CARD_F_GATE,
			ST21NFCA_EVT_SEND_DATA, skb->data, skb->len);
	kfree_skb(skb);

	return r;
}