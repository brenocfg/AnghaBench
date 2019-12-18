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
typedef  int u32 ;
struct ufs_hba {TYPE_1__* active_uic_cmd; } ;
struct TYPE_2__ {scalar_t__ command; } ;

/* Variables and functions */
 int UFSHCD_UIC_HIBERN8_MASK ; 
 scalar_t__ UIC_CMD_DME_HIBER_ENTER ; 
 scalar_t__ UIC_CMD_DME_HIBER_EXIT ; 
 int /*<<< orphan*/  ufshcd_is_auto_hibern8_supported (struct ufs_hba*) ; 

__attribute__((used)) static bool ufshcd_is_auto_hibern8_error(struct ufs_hba *hba,
					 u32 intr_mask)
{
	if (!ufshcd_is_auto_hibern8_supported(hba))
		return false;

	if (!(intr_mask & UFSHCD_UIC_HIBERN8_MASK))
		return false;

	if (hba->active_uic_cmd &&
	    (hba->active_uic_cmd->command == UIC_CMD_DME_HIBER_ENTER ||
	    hba->active_uic_cmd->command == UIC_CMD_DME_HIBER_EXIT))
		return false;

	return true;
}