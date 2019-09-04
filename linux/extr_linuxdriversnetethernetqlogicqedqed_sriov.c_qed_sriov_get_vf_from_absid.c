#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct qed_vf_info {int dummy; } ;
struct qed_hwfn {TYPE_3__* pf_iov_info; TYPE_2__* cdev; } ;
struct TYPE_6__ {struct qed_vf_info* vfs_array; } ;
struct TYPE_5__ {TYPE_1__* p_iov_info; } ;
struct TYPE_4__ {scalar_t__ first_vf_in_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  _qed_iov_pf_sanity_check (struct qed_hwfn*,size_t,int) ; 

__attribute__((used)) static struct qed_vf_info *qed_sriov_get_vf_from_absid(struct qed_hwfn *p_hwfn,
						       u16 abs_vfid)
{
	u8 min = (u8) p_hwfn->cdev->p_iov_info->first_vf_in_pf;

	if (!_qed_iov_pf_sanity_check(p_hwfn, (int)abs_vfid - min, false)) {
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "Got indication for VF [abs 0x%08x] that cannot be handled by PF\n",
			   abs_vfid);
		return NULL;
	}

	return &p_hwfn->pf_iov_info->vfs_array[(u8) abs_vfid - min];
}