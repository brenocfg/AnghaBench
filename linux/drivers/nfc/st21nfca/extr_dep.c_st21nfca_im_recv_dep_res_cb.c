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
typedef  int u8 ;
struct TYPE_4__ {int to; int /*<<< orphan*/  curr_nfc_dep_pni; } ;
struct st21nfca_hci_info {int async_cb_type; TYPE_2__ dep_info; TYPE_1__* hdev; } ;
struct st21nfca_dep_req_res {int /*<<< orphan*/  pfb; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
#define  ST21NFCA_CB_TYPE_READER_F 131 
 int ST21NFCA_NFCIP1_DEP_REQ ; 
 int ST21NFCA_NFCIP1_REQ ; 
 int /*<<< orphan*/  ST21NFCA_NFC_DEP_DID_BIT_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST21NFCA_NFC_DEP_NAD_BIT_SET (int /*<<< orphan*/ ) ; 
#define  ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU 130 
#define  ST21NFCA_NFC_DEP_PFB_I_PDU 129 
 int /*<<< orphan*/  ST21NFCA_NFC_DEP_PFB_PNI (int /*<<< orphan*/ ) ; 
#define  ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU 128 
 int /*<<< orphan*/  ST21NFCA_NFC_DEP_PFB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_tm_data_received (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st21nfca_im_send_pdu (struct st21nfca_hci_info*,struct sk_buff*) ; 

__attribute__((used)) static void st21nfca_im_recv_dep_res_cb(void *context, struct sk_buff *skb,
					int err)
{
	struct st21nfca_hci_info *info = context;
	struct st21nfca_dep_req_res *dep_res;

	int size;

	if (err != 0)
		return;

	if (!skb)
		return;

	switch (info->async_cb_type) {
	case ST21NFCA_CB_TYPE_READER_F:
		dep_res = (struct st21nfca_dep_req_res *)skb->data;

		size = 3;
		if (skb->len < size)
			goto exit;

		if (ST21NFCA_NFC_DEP_DID_BIT_SET(dep_res->pfb))
			size++;
		if (ST21NFCA_NFC_DEP_NAD_BIT_SET(dep_res->pfb))
			size++;

		if (skb->len < size)
			goto exit;

		skb_trim(skb, skb->len - 1);

		/* Receiving DEP_REQ - Decoding */
		switch (ST21NFCA_NFC_DEP_PFB_TYPE(dep_res->pfb)) {
		case ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU:
			pr_err("Received a ACK/NACK PDU\n");
			/* fall through */
		case ST21NFCA_NFC_DEP_PFB_I_PDU:
			info->dep_info.curr_nfc_dep_pni =
			    ST21NFCA_NFC_DEP_PFB_PNI(dep_res->pfb + 1);
			size++;
			skb_pull(skb, size);
			nfc_tm_data_received(info->hdev->ndev, skb);
			break;
		case ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU:
			pr_err("Received a SUPERVISOR PDU\n");
			skb_pull(skb, size);
			*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_REQ;
			*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_REQ;
			*(u8 *)skb_push(skb, 1) = skb->len;
			*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

			st21nfca_im_send_pdu(info, skb);
			break;
		}

		return;
	default:
		break;
	}

exit:
	kfree_skb(skb);
}