#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct virtchnl_iwarp_qvlist_info {int num_vectors; struct virtchnl_iwarp_qv_info* qv_info; } ;
struct virtchnl_iwarp_qv_info {size_t v_idx; scalar_t__ ceq_idx; size_t itr_idx; scalar_t__ aeq_idx; } ;
struct i40e_vf {size_t vf_id; TYPE_2__* qvlist_info; struct i40e_pf* pf; } ;
struct TYPE_4__ {size_t num_msix_vectors_vf; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct TYPE_5__ {int num_vectors; struct virtchnl_iwarp_qv_info* qv_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I40E_QUEUE_INVALID_IDX ; 
 size_t I40E_QUEUE_TYPE_PE_CEQ ; 
 int /*<<< orphan*/  I40E_VPINT_AEQCTL (size_t) ; 
 size_t I40E_VPINT_AEQCTL_CAUSE_ENA_MASK ; 
 size_t I40E_VPINT_AEQCTL_ITR_INDX_SHIFT ; 
 size_t I40E_VPINT_AEQCTL_MSIX_INDX_SHIFT ; 
 int /*<<< orphan*/  I40E_VPINT_CEQCTL (size_t) ; 
 size_t I40E_VPINT_CEQCTL_CAUSE_ENA_MASK ; 
 size_t I40E_VPINT_CEQCTL_ITR_INDX_SHIFT ; 
 size_t I40E_VPINT_CEQCTL_MSIX_INDX_SHIFT ; 
 size_t I40E_VPINT_CEQCTL_NEXTQ_INDX_SHIFT ; 
 size_t I40E_VPINT_CEQCTL_NEXTQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  I40E_VPINT_LNKLSTN (size_t) ; 
 size_t I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK ; 
 size_t I40E_VPINT_LNKLSTN_FIRSTQ_INDX_SHIFT ; 
 size_t I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_MASK ; 
 size_t I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vector_id (struct i40e_vf*,size_t) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int i40e_config_iwarp_qvlist(struct i40e_vf *vf,
				    struct virtchnl_iwarp_qvlist_info *qvlist_info)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	struct virtchnl_iwarp_qv_info *qv_info;
	u32 v_idx, i, reg_idx, reg;
	u32 next_q_idx, next_q_type;
	u32 msix_vf, size;

	size = sizeof(struct virtchnl_iwarp_qvlist_info) +
	       (sizeof(struct virtchnl_iwarp_qv_info) *
						(qvlist_info->num_vectors - 1));
	vf->qvlist_info = kzalloc(size, GFP_KERNEL);
	if (!vf->qvlist_info)
		return -ENOMEM;

	vf->qvlist_info->num_vectors = qvlist_info->num_vectors;

	msix_vf = pf->hw.func_caps.num_msix_vectors_vf;
	for (i = 0; i < qvlist_info->num_vectors; i++) {
		qv_info = &qvlist_info->qv_info[i];
		if (!qv_info)
			continue;
		v_idx = qv_info->v_idx;

		/* Validate vector id belongs to this vf */
		if (!i40e_vc_isvalid_vector_id(vf, v_idx))
			goto err;

		vf->qvlist_info->qv_info[i] = *qv_info;

		reg_idx = ((msix_vf - 1) * vf->vf_id) + (v_idx - 1);
		/* We might be sharing the interrupt, so get the first queue
		 * index and type, push it down the list by adding the new
		 * queue on top. Also link it with the new queue in CEQCTL.
		 */
		reg = rd32(hw, I40E_VPINT_LNKLSTN(reg_idx));
		next_q_idx = ((reg & I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK) >>
				I40E_VPINT_LNKLSTN_FIRSTQ_INDX_SHIFT);
		next_q_type = ((reg & I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_MASK) >>
				I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);

		if (qv_info->ceq_idx != I40E_QUEUE_INVALID_IDX) {
			reg_idx = (msix_vf - 1) * vf->vf_id + qv_info->ceq_idx;
			reg = (I40E_VPINT_CEQCTL_CAUSE_ENA_MASK |
			(v_idx << I40E_VPINT_CEQCTL_MSIX_INDX_SHIFT) |
			(qv_info->itr_idx << I40E_VPINT_CEQCTL_ITR_INDX_SHIFT) |
			(next_q_type << I40E_VPINT_CEQCTL_NEXTQ_TYPE_SHIFT) |
			(next_q_idx << I40E_VPINT_CEQCTL_NEXTQ_INDX_SHIFT));
			wr32(hw, I40E_VPINT_CEQCTL(reg_idx), reg);

			reg_idx = ((msix_vf - 1) * vf->vf_id) + (v_idx - 1);
			reg = (qv_info->ceq_idx &
			       I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK) |
			       (I40E_QUEUE_TYPE_PE_CEQ <<
			       I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);
			wr32(hw, I40E_VPINT_LNKLSTN(reg_idx), reg);
		}

		if (qv_info->aeq_idx != I40E_QUEUE_INVALID_IDX) {
			reg = (I40E_VPINT_AEQCTL_CAUSE_ENA_MASK |
			(v_idx << I40E_VPINT_AEQCTL_MSIX_INDX_SHIFT) |
			(qv_info->itr_idx << I40E_VPINT_AEQCTL_ITR_INDX_SHIFT));

			wr32(hw, I40E_VPINT_AEQCTL(vf->vf_id), reg);
		}
	}

	return 0;
err:
	kfree(vf->qvlist_info);
	vf->qvlist_info = NULL;
	return -EINVAL;
}