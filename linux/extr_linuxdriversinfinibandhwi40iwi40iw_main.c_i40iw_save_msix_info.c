#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i40iw_msix_vector {int dummy; } ;
struct i40iw_device {int msix_count; int msix_shared; TYPE_2__* iw_msixtbl; struct i40e_qvlist_info* iw_qvlist; } ;
struct i40e_qvlist_info {size_t num_vectors; struct i40e_qv_info* qv_info; } ;
struct i40e_qv_info {int itr_idx; int /*<<< orphan*/  v_idx; void* ceq_idx; void* aeq_idx; } ;
struct i40e_info {int msix_count; TYPE_1__* msix_entries; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_4__ {int cpu_affinity; int /*<<< orphan*/  idx; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* I40E_QUEUE_INVALID_IDX ; 
 int I40IW_ERR_CONFIG ; 
 int I40IW_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t num_online_cpus () ; 

__attribute__((used)) static enum i40iw_status_code i40iw_save_msix_info(struct i40iw_device *iwdev,
						   struct i40e_info *ldev)
{
	struct i40e_qvlist_info *iw_qvlist;
	struct i40e_qv_info *iw_qvinfo;
	u32 ceq_idx;
	u32 i;
	u32 size;

	if (!ldev->msix_count) {
		i40iw_pr_err("No MSI-X vectors\n");
		return I40IW_ERR_CONFIG;
	}

	iwdev->msix_count = ldev->msix_count;

	size = sizeof(struct i40iw_msix_vector) * iwdev->msix_count;
	size += sizeof(struct i40e_qvlist_info);
	size +=  sizeof(struct i40e_qv_info) * iwdev->msix_count - 1;
	iwdev->iw_msixtbl = kzalloc(size, GFP_KERNEL);

	if (!iwdev->iw_msixtbl)
		return I40IW_ERR_NO_MEMORY;
	iwdev->iw_qvlist = (struct i40e_qvlist_info *)(&iwdev->iw_msixtbl[iwdev->msix_count]);
	iw_qvlist = iwdev->iw_qvlist;
	iw_qvinfo = iw_qvlist->qv_info;
	iw_qvlist->num_vectors = iwdev->msix_count;
	if (iwdev->msix_count <= num_online_cpus())
		iwdev->msix_shared = true;
	for (i = 0, ceq_idx = 0; i < iwdev->msix_count; i++, iw_qvinfo++) {
		iwdev->iw_msixtbl[i].idx = ldev->msix_entries[i].entry;
		iwdev->iw_msixtbl[i].irq = ldev->msix_entries[i].vector;
		iwdev->iw_msixtbl[i].cpu_affinity = ceq_idx;
		if (i == 0) {
			iw_qvinfo->aeq_idx = 0;
			if (iwdev->msix_shared)
				iw_qvinfo->ceq_idx = ceq_idx++;
			else
				iw_qvinfo->ceq_idx = I40E_QUEUE_INVALID_IDX;
		} else {
			iw_qvinfo->aeq_idx = I40E_QUEUE_INVALID_IDX;
			iw_qvinfo->ceq_idx = ceq_idx++;
		}
		iw_qvinfo->itr_idx = 3;
		iw_qvinfo->v_idx = iwdev->iw_msixtbl[i].idx;
	}
	return 0;
}