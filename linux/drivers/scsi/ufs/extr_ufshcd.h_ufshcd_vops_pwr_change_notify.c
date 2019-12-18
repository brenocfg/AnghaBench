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
struct ufs_pa_layer_attr {int dummy; } ;
struct ufs_hba {TYPE_1__* vops; } ;
struct TYPE_2__ {int (* pwr_change_notify ) (struct ufs_hba*,int,struct ufs_pa_layer_attr*,struct ufs_pa_layer_attr*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct ufs_hba*,int,struct ufs_pa_layer_attr*,struct ufs_pa_layer_attr*) ; 

__attribute__((used)) static inline int ufshcd_vops_pwr_change_notify(struct ufs_hba *hba,
				  bool status,
				  struct ufs_pa_layer_attr *dev_max_params,
				  struct ufs_pa_layer_attr *dev_req_params)
{
	if (hba->vops && hba->vops->pwr_change_notify)
		return hba->vops->pwr_change_notify(hba, status,
					dev_max_params, dev_req_params);

	return -ENOTSUPP;
}