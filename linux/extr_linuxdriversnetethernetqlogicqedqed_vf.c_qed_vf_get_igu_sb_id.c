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
typedef  size_t u16 ;
struct TYPE_5__ {TYPE_1__* hw_sbs; } ;
struct TYPE_6__ {TYPE_2__ resc; } ;
struct qed_vf_iov {TYPE_3__ acquire_resp; } ;
struct qed_hwfn {struct qed_vf_iov* vf_iov_info; } ;
struct TYPE_4__ {size_t hw_sb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 

u16 qed_vf_get_igu_sb_id(struct qed_hwfn *p_hwfn, u16 sb_id)
{
	struct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;

	if (!p_iov) {
		DP_NOTICE(p_hwfn, "vf_sriov_info isn't initialized\n");
		return 0;
	}

	return p_iov->acquire_resp.resc.hw_sbs[sb_id].hw_sb_id;
}