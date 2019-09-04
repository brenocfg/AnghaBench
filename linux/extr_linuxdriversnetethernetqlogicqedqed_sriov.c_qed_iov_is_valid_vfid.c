#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qed_hwfn {TYPE_3__* pf_iov_info; TYPE_4__* cdev; } ;
struct TYPE_8__ {TYPE_1__* p_iov_info; } ;
struct TYPE_7__ {TYPE_2__* vfs_array; } ;
struct TYPE_6__ {scalar_t__ b_malicious; int /*<<< orphan*/  b_init; } ;
struct TYPE_5__ {int total_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (TYPE_4__*,char*) ; 

bool qed_iov_is_valid_vfid(struct qed_hwfn *p_hwfn,
			   int rel_vf_id,
			   bool b_enabled_only, bool b_non_malicious)
{
	if (!p_hwfn->pf_iov_info) {
		DP_NOTICE(p_hwfn->cdev, "No iov info\n");
		return false;
	}

	if ((rel_vf_id >= p_hwfn->cdev->p_iov_info->total_vfs) ||
	    (rel_vf_id < 0))
		return false;

	if ((!p_hwfn->pf_iov_info->vfs_array[rel_vf_id].b_init) &&
	    b_enabled_only)
		return false;

	if ((p_hwfn->pf_iov_info->vfs_array[rel_vf_id].b_malicious) &&
	    b_non_malicious)
		return false;

	return true;
}