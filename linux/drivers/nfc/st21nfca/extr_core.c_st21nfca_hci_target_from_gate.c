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
typedef  int u16 ;
struct nfc_target {int supported_protocols; int sens_res; int sel_res; int nfcid1_len; int /*<<< orphan*/  nfcid1; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int NFC_NFCID1_MAXSIZE ; 
 int NFC_PROTO_FELICA_MASK ; 
 int NFC_PROTO_ISO15693_MASK ; 
 int NFC_PROTO_JEWEL_MASK ; 
#define  ST21NFCA_RF_READER_14443_3_A_GATE 130 
#define  ST21NFCA_RF_READER_F_GATE 129 
#define  ST21NFCA_RF_READER_ISO15693_GATE 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int nfc_hci_sak_to_protocol (int) ; 
 int st21nfca_get_iso14443_3_atqa (struct nfc_hci_dev*,int*) ; 
 int st21nfca_get_iso14443_3_sak (struct nfc_hci_dev*,int*) ; 
 int st21nfca_get_iso14443_3_uid (struct nfc_hci_dev*,int*,int*) ; 
 int st21nfca_get_iso15693_inventory (struct nfc_hci_dev*,struct nfc_target*) ; 

__attribute__((used)) static int st21nfca_hci_target_from_gate(struct nfc_hci_dev *hdev, u8 gate,
					 struct nfc_target *target)
{
	int r, len;
	u16 atqa;
	u8 sak;
	u8 uid[NFC_NFCID1_MAXSIZE];

	switch (gate) {
	case ST21NFCA_RF_READER_F_GATE:
		target->supported_protocols = NFC_PROTO_FELICA_MASK;
		break;
	case ST21NFCA_RF_READER_14443_3_A_GATE:
		/* ISO14443-3 type 1 or 2 tags */
		r = st21nfca_get_iso14443_3_atqa(hdev, &atqa);
		if (r < 0)
			return r;
		if (atqa == 0x000c) {
			target->supported_protocols = NFC_PROTO_JEWEL_MASK;
			target->sens_res = 0x0c00;
		} else {
			r = st21nfca_get_iso14443_3_sak(hdev, &sak);
			if (r < 0)
				return r;

			r = st21nfca_get_iso14443_3_uid(hdev, uid, &len);
			if (r < 0)
				return r;

			target->supported_protocols =
			    nfc_hci_sak_to_protocol(sak);
			if (target->supported_protocols == 0xffffffff)
				return -EPROTO;

			target->sens_res = atqa;
			target->sel_res = sak;
			memcpy(target->nfcid1, uid, len);
			target->nfcid1_len = len;
		}

		break;
	case ST21NFCA_RF_READER_ISO15693_GATE:
		target->supported_protocols = NFC_PROTO_ISO15693_MASK;
		r = st21nfca_get_iso15693_inventory(hdev, target);
		if (r < 0)
			return r;
		break;
	default:
		return -EPROTO;
	}

	return 0;
}