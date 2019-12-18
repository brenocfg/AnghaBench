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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct nfc_target {int* sensf_res; scalar_t__ sensf_res_len; scalar_t__ hci_reader_gate; void* supported_protocols; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ NFC_NFCID1_MAXSIZE ; 
 void* NFC_PROTO_FELICA_MASK ; 
 void* NFC_PROTO_NFC_DEP_MASK ; 
 scalar_t__ NFC_SENSF_RES_MAXSIZE ; 
 scalar_t__ ST21NFCA_RF_READER_F_GATE ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_F_NFCID1 ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_F_NFCID2 ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,scalar_t__,int /*<<< orphan*/ ,struct sk_buff**) ; 

__attribute__((used)) static int st21nfca_hci_complete_target_discovered(struct nfc_hci_dev *hdev,
						u8 gate,
						struct nfc_target *target)
{
	int r;
	struct sk_buff *nfcid_skb = NULL;

	if (gate == ST21NFCA_RF_READER_F_GATE) {
		r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_F_GATE,
				ST21NFCA_RF_READER_F_NFCID2, &nfcid_skb);
		if (r < 0)
			goto exit;

		if (nfcid_skb->len > NFC_SENSF_RES_MAXSIZE) {
			r = -EPROTO;
			goto exit;
		}

		/*
		 * - After the recepton of polling response for type F frame
		 * at 212 or 424 Kbit/s, NFCID2 registry parameters will be
		 * updated.
		 * - After the reception of SEL_RES with NFCIP-1 compliant bit
		 * set for type A frame NFCID1 will be updated
		 */
		if (nfcid_skb->len > 0) {
			/* P2P in type F */
			memcpy(target->sensf_res, nfcid_skb->data,
				nfcid_skb->len);
			target->sensf_res_len = nfcid_skb->len;
			/* NFC Forum Digital Protocol Table 44 */
			if (target->sensf_res[0] == 0x01 &&
			    target->sensf_res[1] == 0xfe)
				target->supported_protocols =
							NFC_PROTO_NFC_DEP_MASK;
			else
				target->supported_protocols =
							NFC_PROTO_FELICA_MASK;
		} else {
			kfree_skb(nfcid_skb);
			nfcid_skb = NULL;
			/* P2P in type A */
			r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_F_GATE,
					ST21NFCA_RF_READER_F_NFCID1,
					&nfcid_skb);
			if (r < 0)
				goto exit;

			if (nfcid_skb->len > NFC_NFCID1_MAXSIZE) {
				r = -EPROTO;
				goto exit;
			}
			memcpy(target->sensf_res, nfcid_skb->data,
				nfcid_skb->len);
			target->sensf_res_len = nfcid_skb->len;
			target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		}
		target->hci_reader_gate = ST21NFCA_RF_READER_F_GATE;
	}
	r = 1;
exit:
	kfree_skb(nfcid_skb);
	return r;
}