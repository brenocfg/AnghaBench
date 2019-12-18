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
struct ufs_hba {TYPE_1__* vops; } ;
typedef  enum uic_cmd_dme { ____Placeholder_uic_cmd_dme } uic_cmd_dme ;
typedef  enum ufs_notify_change_status { ____Placeholder_ufs_notify_change_status } ufs_notify_change_status ;
struct TYPE_2__ {void (* hibern8_notify ) (struct ufs_hba*,int,int) ;} ;

/* Variables and functions */
 void stub1 (struct ufs_hba*,int,int) ; 

__attribute__((used)) static inline void ufshcd_vops_hibern8_notify(struct ufs_hba *hba,
					enum uic_cmd_dme cmd,
					enum ufs_notify_change_status status)
{
	if (hba->vops && hba->vops->hibern8_notify)
		return hba->vops->hibern8_notify(hba, cmd, status);
}