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
struct TYPE_3__ {int to; int /*<<< orphan*/  lri; int /*<<< orphan*/  curr_nfc_dep_pni; int /*<<< orphan*/  idx; } ;
struct st21nfca_hci_info {int async_cb_type; TYPE_2__* hdev; TYPE_1__ dep_info; } ;
struct st21nfca_atr_res {int to; int /*<<< orphan*/  ppi; int /*<<< orphan*/  bri; int /*<<< orphan*/  bsi; int /*<<< orphan*/  did; int /*<<< orphan*/  gbi; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_COMM_PASSIVE ; 
 int /*<<< orphan*/  NFC_RF_INITIATOR ; 
#define  ST21NFCA_CB_TYPE_READER_F 128 
 int /*<<< orphan*/  ST21NFCA_PP2LRI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_dep_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_set_remote_general_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st21nfca_im_send_psl_req (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st21nfca_im_recv_atr_res_cb(void *context, struct sk_buff *skb,
					int err)
{
	struct st21nfca_hci_info *info = context;
	struct st21nfca_atr_res *atr_res;
	int r;

	if (err != 0)
		return;

	if (!skb)
		return;

	switch (info->async_cb_type) {
	case ST21NFCA_CB_TYPE_READER_F:
		skb_trim(skb, skb->len - 1);
		atr_res = (struct st21nfca_atr_res *)skb->data;
		r = nfc_set_remote_general_bytes(info->hdev->ndev,
				atr_res->gbi,
				skb->len - sizeof(struct st21nfca_atr_res));
		if (r < 0)
			return;

		if (atr_res->to >= 0x0e)
			info->dep_info.to = 0x0e;
		else
			info->dep_info.to = atr_res->to + 1;

		info->dep_info.to |= 0x10;

		r = nfc_dep_link_is_up(info->hdev->ndev, info->dep_info.idx,
					NFC_COMM_PASSIVE, NFC_RF_INITIATOR);
		if (r < 0)
			return;

		info->dep_info.curr_nfc_dep_pni = 0;
		if (ST21NFCA_PP2LRI(atr_res->ppi) != info->dep_info.lri)
			st21nfca_im_send_psl_req(info->hdev, atr_res->did,
						atr_res->bsi, atr_res->bri,
						ST21NFCA_PP2LRI(atr_res->ppi));
		break;
	default:
		kfree_skb(skb);
		break;
	}
}