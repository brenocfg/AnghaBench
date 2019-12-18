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
struct ufshcd_lrb {int task_tag; int intr_cmd; scalar_t__ lun; int /*<<< orphan*/ * sense_buffer; scalar_t__ sense_bufflen; int /*<<< orphan*/ * cmd; } ;
struct TYPE_2__ {int type; } ;
struct ufs_hba {TYPE_1__ dev_cmd; } ;
typedef  enum dev_cmd_type { ____Placeholder_dev_cmd_type } dev_cmd_type ;

/* Variables and functions */
 int ufshcd_comp_devman_upiu (struct ufs_hba*,struct ufshcd_lrb*) ; 

__attribute__((used)) static int ufshcd_compose_dev_cmd(struct ufs_hba *hba,
		struct ufshcd_lrb *lrbp, enum dev_cmd_type cmd_type, int tag)
{
	lrbp->cmd = NULL;
	lrbp->sense_bufflen = 0;
	lrbp->sense_buffer = NULL;
	lrbp->task_tag = tag;
	lrbp->lun = 0; /* device management cmd is not specific to any LUN */
	lrbp->intr_cmd = true; /* No interrupt aggregation */
	hba->dev_cmd.type = cmd_type;

	return ufshcd_comp_devman_upiu(hba, lrbp);
}