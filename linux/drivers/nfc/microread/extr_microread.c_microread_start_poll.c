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
typedef  int u32 ;
struct nfc_hci_dev {int* gb; int gb_len; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICROREAD_EVT_MREAD_DISCOVERY_START_SOME ; 
 int /*<<< orphan*/  MICROREAD_EVT_MREAD_DISCOVERY_STOP ; 
 int /*<<< orphan*/  MICROREAD_GATE_ID_MREAD_ISO_A ; 
 int /*<<< orphan*/  MICROREAD_GATE_ID_P2P_INITIATOR ; 
 int /*<<< orphan*/  MICROREAD_GATE_ID_P2P_TARGET ; 
 int /*<<< orphan*/  MICROREAD_PAR_P2P_INITIATOR_GI ; 
 int /*<<< orphan*/  MICROREAD_PAR_P2P_TARGET_GT ; 
 int /*<<< orphan*/  MICROREAD_PAR_P2P_TARGET_MODE ; 
 int NFC_PROTO_FELICA_MASK ; 
 int NFC_PROTO_ISO14443_B_MASK ; 
 int NFC_PROTO_ISO14443_MASK ; 
 int NFC_PROTO_JEWEL_MASK ; 
 int NFC_PROTO_MIFARE_MASK ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 int* nfc_get_local_general_bytes (int /*<<< orphan*/ ,int*) ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int nfc_hci_set_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int microread_start_poll(struct nfc_hci_dev *hdev,
				u32 im_protocols, u32 tm_protocols)
{
	int r;

	u8 param[2];
	u8 mode;

	param[0] = 0x00;
	param[1] = 0x00;

	if (im_protocols & NFC_PROTO_ISO14443_MASK)
		param[0] |= (1 << 2);

	if (im_protocols & NFC_PROTO_ISO14443_B_MASK)
		param[0] |= 1;

	if (im_protocols & NFC_PROTO_MIFARE_MASK)
		param[1] |= 1;

	if (im_protocols & NFC_PROTO_JEWEL_MASK)
		param[0] |= (1 << 1);

	if (im_protocols & NFC_PROTO_FELICA_MASK)
		param[0] |= (1 << 5);

	if (im_protocols & NFC_PROTO_NFC_DEP_MASK)
		param[1] |= (1 << 1);

	if ((im_protocols | tm_protocols) & NFC_PROTO_NFC_DEP_MASK) {
		hdev->gb = nfc_get_local_general_bytes(hdev->ndev,
						       &hdev->gb_len);
		if (hdev->gb == NULL || hdev->gb_len == 0) {
			im_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
			tm_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
		}
	}

	r = nfc_hci_send_event(hdev, MICROREAD_GATE_ID_MREAD_ISO_A,
			       MICROREAD_EVT_MREAD_DISCOVERY_STOP, NULL, 0);
	if (r)
		return r;

	mode = 0xff;
	r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
			      MICROREAD_PAR_P2P_TARGET_MODE, &mode, 1);
	if (r)
		return r;

	if (im_protocols & NFC_PROTO_NFC_DEP_MASK) {
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_INITIATOR,
				      MICROREAD_PAR_P2P_INITIATOR_GI,
				      hdev->gb, hdev->gb_len);
		if (r)
			return r;
	}

	if (tm_protocols & NFC_PROTO_NFC_DEP_MASK) {
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
				      MICROREAD_PAR_P2P_TARGET_GT,
				      hdev->gb, hdev->gb_len);
		if (r)
			return r;

		mode = 0x02;
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
				      MICROREAD_PAR_P2P_TARGET_MODE, &mode, 1);
		if (r)
			return r;
	}

	return nfc_hci_send_event(hdev, MICROREAD_GATE_ID_MREAD_ISO_A,
				  MICROREAD_EVT_MREAD_DISCOVERY_START_SOME,
				  param, 2);
}