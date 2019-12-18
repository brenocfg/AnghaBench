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
struct ufs_hba {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UFS_VERSION ; 
 int UFSHCD_QUIRK_BROKEN_UFS_HCI_VERSION ; 
 int /*<<< orphan*/  ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_vops_get_ufs_hci_version (struct ufs_hba*) ; 

__attribute__((used)) static inline u32 ufshcd_get_ufs_version(struct ufs_hba *hba)
{
	if (hba->quirks & UFSHCD_QUIRK_BROKEN_UFS_HCI_VERSION)
		return ufshcd_vops_get_ufs_hci_version(hba);

	return ufshcd_readl(hba, REG_UFS_VERSION);
}