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
struct ufs_hisi_host {int dummy; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int BIT_SYSCTRL_REF_CLOCK_EN ; 
 int BIT_UFS_REFCLK_ISO_EN ; 
 int BIT_UFS_REFCLK_SRC_SEl ; 
 int /*<<< orphan*/  PHY_CLK_CTRL ; 
 int /*<<< orphan*/  PHY_ISO_EN ; 
 int /*<<< orphan*/  UFS_SYSCTRL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  ufs_sys_ctrl_clr_bits (struct ufs_hisi_host*,int,int /*<<< orphan*/ ) ; 
 int ufs_sys_ctrl_readl (struct ufs_hisi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_sys_ctrl_set_bits (struct ufs_hisi_host*,int,int /*<<< orphan*/ ) ; 
 struct ufs_hisi_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static void ufs_hisi_clk_init(struct ufs_hba *hba)
{
	struct ufs_hisi_host *host = ufshcd_get_variant(hba);

	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	if (ufs_sys_ctrl_readl(host, PHY_CLK_CTRL) & BIT_SYSCTRL_REF_CLOCK_EN)
		mdelay(1);
	/* use abb clk */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_SRC_SEl, UFS_SYSCTRL);
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_ISO_EN, PHY_ISO_EN);
	/* open mphy ref clk */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
}