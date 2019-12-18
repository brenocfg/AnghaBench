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
typedef  int u32 ;
struct ufs_hba {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UTP_TASK_REQ_LIST_CLEAR ; 
 int UFSHCI_QUIRK_BROKEN_REQ_LIST_CLR ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ufshcd_utmrl_clear(struct ufs_hba *hba, u32 pos)
{
	if (hba->quirks & UFSHCI_QUIRK_BROKEN_REQ_LIST_CLR)
		ufshcd_writel(hba, (1 << pos), REG_UTP_TASK_REQ_LIST_CLEAR);
	else
		ufshcd_writel(hba, ~(1 << pos), REG_UTP_TASK_REQ_LIST_CLEAR);
}