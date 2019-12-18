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
typedef  int /*<<< orphan*/  u32 ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CDNS_UFS_REG_PHY_XCFGD1 ; 
 int /*<<< orphan*/  ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_ufs_m31_16nm_phy_initialization(struct ufs_hba *hba)
{
	u32 data;

	/* Increase RX_Advanced_Min_ActivateTime_Capability */
	data = ufshcd_readl(hba, CDNS_UFS_REG_PHY_XCFGD1);
	data |= BIT(24);
	ufshcd_writel(hba, data, CDNS_UFS_REG_PHY_XCFGD1);

	return 0;
}