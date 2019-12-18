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
typedef  int u32 ;
struct ufs_hba {int /*<<< orphan*/ * uic_async_done; TYPE_1__* active_uic_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; int /*<<< orphan*/  argument3; int /*<<< orphan*/  argument2; } ;

/* Variables and functions */
 int UFSHCD_UIC_PWR_MASK ; 
 int UIC_COMMAND_COMPL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufshcd_get_dme_attr_val (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_get_uic_cmd_result (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_uic_cmd_compl(struct ufs_hba *hba, u32 intr_status)
{
	if ((intr_status & UIC_COMMAND_COMPL) && hba->active_uic_cmd) {
		hba->active_uic_cmd->argument2 |=
			ufshcd_get_uic_cmd_result(hba);
		hba->active_uic_cmd->argument3 =
			ufshcd_get_dme_attr_val(hba);
		complete(&hba->active_uic_cmd->done);
	}

	if ((intr_status & UFSHCD_UIC_PWR_MASK) && hba->uic_async_done)
		complete(hba->uic_async_done);
}