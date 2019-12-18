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
typedef  size_t u8 ;
struct TYPE_4__ {int se_active; int /*<<< orphan*/  req_completion; int /*<<< orphan*/  count_pipes; int /*<<< orphan*/  se_active_timer; int /*<<< orphan*/  expected_pipes; } ;
struct st21nfca_hci_info {TYPE_2__ se_info; } ;
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {TYPE_1__* pipes; } ;
struct TYPE_3__ {size_t gate; int /*<<< orphan*/  dest_host; } ;

/* Variables and functions */
#define  NFC_HCI_ANY_OPEN_PIPE 128 
 int /*<<< orphan*/  NFC_HCI_UICC_HOST_ID ; 
 size_t ST21NFCA_APDU_READER_GATE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 

__attribute__((used)) static void st21nfca_hci_cmd_received(struct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
				struct sk_buff *skb)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	u8 gate = hdev->pipes[pipe].gate;

	pr_debug("cmd: %x\n", cmd);

	switch (cmd) {
	case NFC_HCI_ANY_OPEN_PIPE:
		if (gate != ST21NFCA_APDU_READER_GATE &&
			hdev->pipes[pipe].dest_host != NFC_HCI_UICC_HOST_ID)
			info->se_info.count_pipes++;

		if (info->se_info.count_pipes == info->se_info.expected_pipes) {
			del_timer_sync(&info->se_info.se_active_timer);
			info->se_info.se_active = false;
			info->se_info.count_pipes = 0;
			complete(&info->se_info.req_completion);
		}
	break;
	}
}