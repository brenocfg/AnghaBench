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
struct timer_list {int dummy; } ;
struct TYPE_3__ {int bwi_active; int xch_error; int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct st21nfca_hci_info {TYPE_1__ se_info; int /*<<< orphan*/  hdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bwi_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  ST21NFCA_APDU_READER_GATE ; 
 int /*<<< orphan*/  ST21NFCA_DEVICE_MGNT_GATE ; 
 int /*<<< orphan*/  ST21NFCA_EVT_SE_HARD_RESET ; 
 int /*<<< orphan*/  ST21NFCA_EVT_SE_SOFT_RESET ; 
 struct st21nfca_hci_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct st21nfca_hci_info* info ; 
 int /*<<< orphan*/  nfc_hci_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_2__ se_info ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st21nfca_se_wt_timeout(struct timer_list *t)
{
	/*
	 * No answer from the secure element
	 * within the defined timeout.
	 * Let's send a reset request as recovery procedure.
	 * According to the situation, we first try to send a software reset
	 * to the secure element. If the next command is still not
	 * answering in time, we send to the CLF a secure element hardware
	 * reset request.
	 */
	/* hardware reset managed through VCC_UICC_OUT power supply */
	u8 param = 0x01;
	struct st21nfca_hci_info *info = from_timer(info, t,
						    se_info.bwi_timer);

	pr_debug("\n");

	info->se_info.bwi_active = false;

	if (!info->se_info.xch_error) {
		info->se_info.xch_error = true;
		nfc_hci_send_event(info->hdev, ST21NFCA_APDU_READER_GATE,
				ST21NFCA_EVT_SE_SOFT_RESET, NULL, 0);
	} else {
		info->se_info.xch_error = false;
		nfc_hci_send_event(info->hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_EVT_SE_HARD_RESET, &param, 1);
	}
	info->se_info.cb(info->se_info.cb_context, NULL, 0, -ETIME);
}