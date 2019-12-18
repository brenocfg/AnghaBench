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
typedef  int /*<<< orphan*/  u32 ;
struct ufshcd_lrb {int /*<<< orphan*/  command_type; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ufs_hba {scalar_t__ ufs_version; TYPE_1__ dev_cmd; } ;

/* Variables and functions */
 scalar_t__ DEV_CMD_TYPE_NOP ; 
 scalar_t__ DEV_CMD_TYPE_QUERY ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int EINVAL ; 
 scalar_t__ UFSHCI_VERSION_10 ; 
 scalar_t__ UFSHCI_VERSION_11 ; 
 int /*<<< orphan*/  UTP_CMD_TYPE_DEV_MANAGE ; 
 int /*<<< orphan*/  UTP_CMD_TYPE_UFS_STORAGE ; 
 int /*<<< orphan*/  ufshcd_prepare_req_desc_hdr (struct ufshcd_lrb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_prepare_utp_nop_upiu (struct ufshcd_lrb*) ; 
 int /*<<< orphan*/  ufshcd_prepare_utp_query_req_upiu (struct ufs_hba*,struct ufshcd_lrb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_comp_devman_upiu(struct ufs_hba *hba, struct ufshcd_lrb *lrbp)
{
	u32 upiu_flags;
	int ret = 0;

	if ((hba->ufs_version == UFSHCI_VERSION_10) ||
	    (hba->ufs_version == UFSHCI_VERSION_11))
		lrbp->command_type = UTP_CMD_TYPE_DEV_MANAGE;
	else
		lrbp->command_type = UTP_CMD_TYPE_UFS_STORAGE;

	ufshcd_prepare_req_desc_hdr(lrbp, &upiu_flags, DMA_NONE);
	if (hba->dev_cmd.type == DEV_CMD_TYPE_QUERY)
		ufshcd_prepare_utp_query_req_upiu(hba, lrbp, upiu_flags);
	else if (hba->dev_cmd.type == DEV_CMD_TYPE_NOP)
		ufshcd_prepare_utp_nop_upiu(lrbp);
	else
		ret = -EINVAL;

	return ret;
}