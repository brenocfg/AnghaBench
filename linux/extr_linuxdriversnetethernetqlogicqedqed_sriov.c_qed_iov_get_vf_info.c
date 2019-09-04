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
typedef  size_t u16 ;
struct qed_vf_info {int dummy; } ;
struct qed_hwfn {TYPE_1__* pf_iov_info; int /*<<< orphan*/  cdev; } ;
struct TYPE_2__ {struct qed_vf_info* vfs_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,size_t) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ qed_iov_is_valid_vfid (struct qed_hwfn*,size_t,int,int) ; 

__attribute__((used)) static struct qed_vf_info *qed_iov_get_vf_info(struct qed_hwfn *p_hwfn,
					       u16 relative_vf_id,
					       bool b_enabled_only)
{
	struct qed_vf_info *vf = NULL;

	if (!p_hwfn->pf_iov_info) {
		DP_NOTICE(p_hwfn->cdev, "No iov info\n");
		return NULL;
	}

	if (qed_iov_is_valid_vfid(p_hwfn, relative_vf_id,
				  b_enabled_only, false))
		vf = &p_hwfn->pf_iov_info->vfs_array[relative_vf_id];
	else
		DP_ERR(p_hwfn, "qed_iov_get_vf_info: VF[%d] is not enabled\n",
		       relative_vf_id);

	return vf;
}