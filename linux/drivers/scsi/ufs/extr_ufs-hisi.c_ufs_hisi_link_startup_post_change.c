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
 int /*<<< orphan*/  CLOCK_GATE_BYPASS ; 
 int /*<<< orphan*/  MASK_UFS_CLK_GATE_BYPASS ; 
 int /*<<< orphan*/  MASK_UFS_SYSCRTL_BYPASS ; 
 int /*<<< orphan*/  UFS_SYSCTRL ; 
 int /*<<< orphan*/  UIC_ARG_MIB (int) ; 
 int /*<<< orphan*/  ufs_sys_ctrl_clr_bits (struct ufs_hisi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_dme_set (struct ufs_hba*,int /*<<< orphan*/ ,int) ; 
 struct ufs_hisi_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_hisi_link_startup_post_change(struct ufs_hba *hba)
{
	struct ufs_hisi_host *host = ufshcd_get_variant(hba);

	/* Unipro DL_AFC0CreditThreshold */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x2044), 0x0);
	/* Unipro DL_TC0OutAckThreshold */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x2045), 0x0);
	/* Unipro DL_TC0TXFCThreshold */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x2040), 0x9);

	/* not bypass ufs clk gate */
	ufs_sys_ctrl_clr_bits(host, MASK_UFS_CLK_GATE_BYPASS,
						CLOCK_GATE_BYPASS);
	ufs_sys_ctrl_clr_bits(host, MASK_UFS_SYSCRTL_BYPASS,
						UFS_SYSCTRL);

	/* select received symbol cnt */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09a), 0x80000000);
	 /* reset counter0 and enable */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09c), 0x00000005);

	return 0;
}