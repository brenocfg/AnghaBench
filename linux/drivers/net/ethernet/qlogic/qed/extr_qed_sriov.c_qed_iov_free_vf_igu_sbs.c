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
typedef  scalar_t__ u32 ;
struct qed_vf_info {int num_sbs; int* igu_sbs; } ;
struct qed_ptt {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  free_cnt_iov; } ;
struct qed_igu_info {TYPE_2__ usage; TYPE_1__* entry; } ;
struct TYPE_6__ {struct qed_igu_info* p_igu_info; } ;
struct qed_hwfn {TYPE_3__ hw_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_MAPPING_LINE_VALID ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 int /*<<< orphan*/  QED_IGU_STATUS_FREE ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void qed_iov_free_vf_igu_sbs(struct qed_hwfn *p_hwfn,
				    struct qed_ptt *p_ptt,
				    struct qed_vf_info *vf)
{
	struct qed_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	int idx, igu_id;
	u32 addr, val;

	/* Invalidate igu CAM lines and mark them as free */
	for (idx = 0; idx < vf->num_sbs; idx++) {
		igu_id = vf->igu_sbs[idx];
		addr = IGU_REG_MAPPING_MEMORY + sizeof(u32) * igu_id;

		val = qed_rd(p_hwfn, p_ptt, addr);
		SET_FIELD(val, IGU_MAPPING_LINE_VALID, 0);
		qed_wr(p_hwfn, p_ptt, addr, val);

		p_info->entry[igu_id].status |= QED_IGU_STATUS_FREE;
		p_hwfn->hw_info.p_igu_info->usage.free_cnt_iov++;
	}

	vf->num_sbs = 0;
}