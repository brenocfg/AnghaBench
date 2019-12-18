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
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UFS_SYS1CLK_1US ; 
 int /*<<< orphan*/  ufs_qcom_dump_regs_wrapper ; 
 int /*<<< orphan*/  ufs_qcom_print_hw_debug_reg_all (struct ufs_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_qcom_print_unipro_testbus (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufs_qcom_testbus_read (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_dump_regs (struct ufs_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ufs_qcom_dump_dbg_regs(struct ufs_hba *hba)
{
	ufshcd_dump_regs(hba, REG_UFS_SYS1CLK_1US, 16 * 4,
			 "HCI Vendor Specific Registers ");

	/* sleep a bit intermittently as we are dumping too much data */
	ufs_qcom_print_hw_debug_reg_all(hba, NULL, ufs_qcom_dump_regs_wrapper);
	usleep_range(1000, 1100);
	ufs_qcom_testbus_read(hba);
	usleep_range(1000, 1100);
	ufs_qcom_print_unipro_testbus(hba);
	usleep_range(1000, 1100);
}