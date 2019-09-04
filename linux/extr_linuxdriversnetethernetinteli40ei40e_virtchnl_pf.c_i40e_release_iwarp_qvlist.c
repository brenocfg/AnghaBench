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
typedef  size_t u32 ;
struct virtchnl_iwarp_qvlist_info {size_t num_vectors; struct virtchnl_iwarp_qv_info* qv_info; } ;
struct virtchnl_iwarp_qv_info {size_t v_idx; scalar_t__ ceq_idx; } ;
struct i40e_vf {size_t vf_id; struct virtchnl_iwarp_qvlist_info* qvlist_info; struct i40e_pf* pf; } ;
struct TYPE_2__ {size_t num_msix_vectors_vf; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 scalar_t__ I40E_QUEUE_INVALID_IDX ; 
 int /*<<< orphan*/  I40E_VPINT_CEQCTL (size_t) ; 
 size_t I40E_VPINT_CEQCTL_NEXTQ_INDX_MASK ; 
 size_t I40E_VPINT_CEQCTL_NEXTQ_INDX_SHIFT ; 
 size_t I40E_VPINT_CEQCTL_NEXTQ_TYPE_MASK ; 
 size_t I40E_VPINT_CEQCTL_NEXTQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  I40E_VPINT_LNKLSTN (size_t) ; 
 size_t I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK ; 
 size_t I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  kfree (struct virtchnl_iwarp_qvlist_info*) ; 
 size_t rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void i40e_release_iwarp_qvlist(struct i40e_vf *vf)
{
	struct i40e_pf *pf = vf->pf;
	struct virtchnl_iwarp_qvlist_info *qvlist_info = vf->qvlist_info;
	u32 msix_vf;
	u32 i;

	if (!vf->qvlist_info)
		return;

	msix_vf = pf->hw.func_caps.num_msix_vectors_vf;
	for (i = 0; i < qvlist_info->num_vectors; i++) {
		struct virtchnl_iwarp_qv_info *qv_info;
		u32 next_q_index, next_q_type;
		struct i40e_hw *hw = &pf->hw;
		u32 v_idx, reg_idx, reg;

		qv_info = &qvlist_info->qv_info[i];
		if (!qv_info)
			continue;
		v_idx = qv_info->v_idx;
		if (qv_info->ceq_idx != I40E_QUEUE_INVALID_IDX) {
			/* Figure out the queue after CEQ and make that the
			 * first queue.
			 */
			reg_idx = (msix_vf - 1) * vf->vf_id + qv_info->ceq_idx;
			reg = rd32(hw, I40E_VPINT_CEQCTL(reg_idx));
			next_q_index = (reg & I40E_VPINT_CEQCTL_NEXTQ_INDX_MASK)
					>> I40E_VPINT_CEQCTL_NEXTQ_INDX_SHIFT;
			next_q_type = (reg & I40E_VPINT_CEQCTL_NEXTQ_TYPE_MASK)
					>> I40E_VPINT_CEQCTL_NEXTQ_TYPE_SHIFT;

			reg_idx = ((msix_vf - 1) * vf->vf_id) + (v_idx - 1);
			reg = (next_q_index &
			       I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK) |
			       (next_q_type <<
			       I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);

			wr32(hw, I40E_VPINT_LNKLSTN(reg_idx), reg);
		}
	}
	kfree(vf->qvlist_info);
	vf->qvlist_info = NULL;
}