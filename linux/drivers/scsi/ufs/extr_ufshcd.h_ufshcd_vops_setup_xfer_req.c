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
struct TYPE_2__ {void (* setup_xfer_req ) (struct ufs_hba*,int,int) ;} ;

/* Variables and functions */
 void stub1 (struct ufs_hba*,int,int) ; 

__attribute__((used)) static inline void ufshcd_vops_setup_xfer_req(struct ufs_hba *hba, int tag,
					bool is_scsi_cmd)
{
	if (hba->vops && hba->vops->setup_xfer_req)
		return hba->vops->setup_xfer_req(hba, tag, is_scsi_cmd);
}