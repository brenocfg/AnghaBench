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
 int /*<<< orphan*/  MASK_UFS_PHY_SOFT_RESET ; 
 int OFFSET_UFS_PHY_SOFT_RESET ; 
 int /*<<< orphan*/  REG_UFS_CFG1 ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  ufshcd_rmwl (struct ufs_hba*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ufs_qcom_deassert_reset(struct ufs_hba *hba)
{
	ufshcd_rmwl(hba, MASK_UFS_PHY_SOFT_RESET,
			0 << OFFSET_UFS_PHY_SOFT_RESET, REG_UFS_CFG1);

	/*
	 * Make sure de-assertion of ufs phy reset is written to
	 * register before returning
	 */
	mb();
}