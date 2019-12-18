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
struct st_nci_info {TYPE_1__ se_info; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 

void st_nci_se_deinit(struct nci_dev *ndev)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);

	if (info->se_info.bwi_active)
		del_timer_sync(&info->se_info.bwi_timer);
	if (info->se_info.se_active)
		del_timer_sync(&info->se_info.se_active_timer);

	info->se_info.se_active = false;
	info->se_info.bwi_active = false;
}