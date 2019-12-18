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
struct nfc_target {int hci_reader_gate; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NFC_HCI_RF_READER_A_GATE 130 
#define  NFC_HCI_RF_READER_B_GATE 129 
#define  ST21NFCA_RF_READER_14443_3_A_GATE 128 
 int /*<<< orphan*/  ST21NFCA_RF_READER_CMD_PRESENCE_CHECK ; 
 int /*<<< orphan*/  ST21NFCA_WR_XCHG_DATA ; 
 int nfc_hci_send_cmd (struct nfc_hci_dev*,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st21nfca_hci_check_presence(struct nfc_hci_dev *hdev,
				       struct nfc_target *target)
{
	u8 fwi = 0x11;

	switch (target->hci_reader_gate) {
	case NFC_HCI_RF_READER_A_GATE:
	case NFC_HCI_RF_READER_B_GATE:
		/*
		 * PRESENCE_CHECK on those gates is available
		 * However, the answer to this command is taking 3 * fwi
		 * if the card is no present.
		 * Instead, we send an empty I-Frame with a very short
		 * configurable fwi ~604µs.
		 */
		return nfc_hci_send_cmd(hdev, target->hci_reader_gate,
					ST21NFCA_WR_XCHG_DATA, &fwi, 1, NULL);
	case ST21NFCA_RF_READER_14443_3_A_GATE:
		return nfc_hci_send_cmd(hdev, target->hci_reader_gate,
					ST21NFCA_RF_READER_CMD_PRESENCE_CHECK,
					NULL, 0, NULL);
	default:
		return -EOPNOTSUPP;
	}
}