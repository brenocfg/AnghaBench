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
struct TYPE_2__ {int bwi_active; int se_active; int xch_error; int /*<<< orphan*/  wt_timeout; scalar_t__ expected_pipes; scalar_t__ count_pipes; int /*<<< orphan*/  se_active_timer; int /*<<< orphan*/  bwi_timer; int /*<<< orphan*/  req_completion; } ;
struct st21nfca_hci_info {TYPE_1__ se_info; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST21NFCA_ATR_DEFAULT_BWI ; 
 int /*<<< orphan*/  ST21NFCA_BWI_TO_TIMEOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  st21nfca_se_activation_timeout ; 
 int /*<<< orphan*/  st21nfca_se_wt_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void st21nfca_se_init(struct nfc_hci_dev *hdev)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	init_completion(&info->se_info.req_completion);
	/* initialize timers */
	timer_setup(&info->se_info.bwi_timer, st21nfca_se_wt_timeout, 0);
	info->se_info.bwi_active = false;

	timer_setup(&info->se_info.se_active_timer,
		    st21nfca_se_activation_timeout, 0);
	info->se_info.se_active = false;

	info->se_info.count_pipes = 0;
	info->se_info.expected_pipes = 0;

	info->se_info.xch_error = false;

	info->se_info.wt_timeout =
			ST21NFCA_BWI_TO_TIMEOUT(ST21NFCA_ATR_DEFAULT_BWI);
}