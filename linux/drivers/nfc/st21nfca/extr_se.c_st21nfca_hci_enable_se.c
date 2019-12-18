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
typedef  int /*<<< orphan*/  u32 ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST21NFCA_APDU_READER_GATE ; 
 int ST21NFCA_ESE_HOST_ID ; 
 int /*<<< orphan*/  ST21NFCA_EVT_SE_SOFT_RESET ; 
 int /*<<< orphan*/  ST21NFCA_SE_MODE_ON ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_remove_se (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st21nfca_hci_control_se (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st21nfca_se_get_atr (struct nfc_hci_dev*) ; 

int st21nfca_hci_enable_se(struct nfc_hci_dev *hdev, u32 se_idx)
{
	int r;

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_status->is_uicc_enable is true should never happen.
	 * Same for eSE.
	 */
	r = st21nfca_hci_control_se(hdev, se_idx, ST21NFCA_SE_MODE_ON);
	if (r == ST21NFCA_ESE_HOST_ID) {
		st21nfca_se_get_atr(hdev);
		r = nfc_hci_send_event(hdev, ST21NFCA_APDU_READER_GATE,
				ST21NFCA_EVT_SE_SOFT_RESET, NULL, 0);
		if (r < 0)
			return r;
	} else if (r < 0) {
		/*
		 * The activation tentative failed, the secure element
		 * is not connected. Remove from the list.
		 */
		nfc_remove_se(hdev->ndev, se_idx);
		return r;
	}

	return 0;
}