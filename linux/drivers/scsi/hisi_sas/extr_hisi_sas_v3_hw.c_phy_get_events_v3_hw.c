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
typedef  scalar_t__ u32 ;
struct sas_phy {int /*<<< orphan*/  running_disparity_error_count; int /*<<< orphan*/  invalid_dword_count; int /*<<< orphan*/  phy_reset_problem_count; int /*<<< orphan*/  loss_of_dword_sync_count; } ;
struct asd_sas_phy {struct sas_phy* phy; } ;
struct hisi_sas_phy {int /*<<< orphan*/  lock; int /*<<< orphan*/  code_violation_err_count; struct asd_sas_phy sas_phy; } ;
struct hisi_hba {struct hisi_sas_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CNT_CODE_ERR ; 
 int /*<<< orphan*/  ERR_CNT_DISP_ERR ; 
 int /*<<< orphan*/  ERR_CNT_DWS_LOST ; 
 int /*<<< orphan*/  ERR_CNT_INVLD_DW ; 
 int /*<<< orphan*/  ERR_CNT_RESET_PROB ; 
 scalar_t__ hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void phy_get_events_v3_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	struct sas_phy *sphy = sas_phy->phy;
	unsigned long flags;
	u32 reg_value;

	spin_lock_irqsave(&phy->lock, flags);

	/* loss dword sync */
	reg_value = hisi_sas_phy_read32(hisi_hba, phy_no, ERR_CNT_DWS_LOST);
	sphy->loss_of_dword_sync_count += reg_value;

	/* phy reset problem */
	reg_value = hisi_sas_phy_read32(hisi_hba, phy_no, ERR_CNT_RESET_PROB);
	sphy->phy_reset_problem_count += reg_value;

	/* invalid dword */
	reg_value = hisi_sas_phy_read32(hisi_hba, phy_no, ERR_CNT_INVLD_DW);
	sphy->invalid_dword_count += reg_value;

	/* disparity err */
	reg_value = hisi_sas_phy_read32(hisi_hba, phy_no, ERR_CNT_DISP_ERR);
	sphy->running_disparity_error_count += reg_value;

	/* code violation error */
	reg_value = hisi_sas_phy_read32(hisi_hba, phy_no, ERR_CNT_CODE_ERR);
	phy->code_violation_err_count += reg_value;

	spin_unlock_irqrestore(&phy->lock, flags);
}