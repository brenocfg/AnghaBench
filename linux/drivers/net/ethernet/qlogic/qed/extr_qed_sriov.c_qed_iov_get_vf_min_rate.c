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
typedef  int /*<<< orphan*/  u16 ;
struct qed_wfq_data {int min_speed; scalar_t__ configured; } ;
struct qed_vf_info {size_t vport_id; } ;
struct TYPE_2__ {struct qed_wfq_data* wfq_data; } ;
struct qed_hwfn {TYPE_1__ qm_info; } ;

/* Variables and functions */
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_iov_get_vf_min_rate(struct qed_hwfn *p_hwfn, int vfid)
{
	struct qed_wfq_data *vf_vp_wfq;
	struct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	if (!vf_info)
		return 0;

	vf_vp_wfq = &p_hwfn->qm_info.wfq_data[vf_info->vport_id];

	if (vf_vp_wfq->configured)
		return vf_vp_wfq->min_speed;
	else
		return 0;
}