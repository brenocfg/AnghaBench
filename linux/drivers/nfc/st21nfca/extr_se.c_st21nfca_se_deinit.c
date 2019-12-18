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
struct TYPE_2__ {int bwi_active; int se_active; int /*<<< orphan*/  se_active_timer; int /*<<< orphan*/  bwi_timer; } ;
struct st21nfca_hci_info {TYPE_1__ se_info; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 

void st21nfca_se_deinit(struct nfc_hci_dev *hdev)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	if (info->se_info.bwi_active)
		del_timer_sync(&info->se_info.bwi_timer);
	if (info->se_info.se_active)
		del_timer_sync(&info->se_info.se_active_timer);

	info->se_info.bwi_active = false;
	info->se_info.se_active = false;
}