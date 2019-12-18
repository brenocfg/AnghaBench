#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct i40e_qvlist_info {size_t num_vectors; struct i40e_qv_info* qv_info; } ;
struct i40e_qv_info {size_t v_idx; scalar_t__ ceq_idx; size_t itr_idx; scalar_t__ aeq_idx; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {size_t iwarp_base_vector; size_t num_iwarp_msix; struct i40e_hw hw; } ;
struct i40e_info {TYPE_1__* qvlist_info; struct i40e_pf* pf; } ;
struct i40e_client {int dummy; } ;
struct TYPE_4__ {size_t num_vectors; struct i40e_qv_info* qv_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t I40E_PFINT_AEQCTL ; 
 size_t I40E_PFINT_AEQCTL_CAUSE_ENA_MASK ; 
 size_t I40E_PFINT_AEQCTL_ITR_INDX_SHIFT ; 
 size_t I40E_PFINT_AEQCTL_MSIX_INDX_SHIFT ; 
 size_t I40E_PFINT_CEQCTL (size_t) ; 
 size_t I40E_PFINT_CEQCTL_CAUSE_ENA_MASK ; 
 size_t I40E_PFINT_CEQCTL_ITR_INDX_SHIFT ; 
 size_t I40E_PFINT_CEQCTL_MSIX_INDX_SHIFT ; 
 size_t I40E_PFINT_CEQCTL_NEXTQ_INDX_SHIFT ; 
 size_t I40E_PFINT_LNKLSTN (size_t) ; 
 size_t I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK ; 
 size_t I40E_PFINT_LNKLSTN_FIRSTQ_TYPE_SHIFT ; 
 size_t I40E_QUEUE_END_OF_LIST ; 
 scalar_t__ I40E_QUEUE_INVALID_IDX ; 
 size_t I40E_QUEUE_TYPE_PE_CEQ ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (TYPE_1__*,struct i40e_qv_info*,size_t) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,size_t,size_t) ; 

__attribute__((used)) static int i40e_client_setup_qvlist(struct i40e_info *ldev,
				    struct i40e_client *client,
				    struct i40e_qvlist_info *qvlist_info)
{
	struct i40e_pf *pf = ldev->pf;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_qv_info *qv_info;
	u32 v_idx, i, reg_idx, reg;

	ldev->qvlist_info = kzalloc(struct_size(ldev->qvlist_info, qv_info,
				    qvlist_info->num_vectors - 1), GFP_KERNEL);
	if (!ldev->qvlist_info)
		return -ENOMEM;
	ldev->qvlist_info->num_vectors = qvlist_info->num_vectors;

	for (i = 0; i < qvlist_info->num_vectors; i++) {
		qv_info = &qvlist_info->qv_info[i];
		if (!qv_info)
			continue;
		v_idx = qv_info->v_idx;

		/* Validate vector id belongs to this client */
		if ((v_idx >= (pf->iwarp_base_vector + pf->num_iwarp_msix)) ||
		    (v_idx < pf->iwarp_base_vector))
			goto err;

		ldev->qvlist_info->qv_info[i] = *qv_info;
		reg_idx = I40E_PFINT_LNKLSTN(v_idx - 1);

		if (qv_info->ceq_idx == I40E_QUEUE_INVALID_IDX) {
			/* Special case - No CEQ mapped on this vector */
			wr32(hw, reg_idx, I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK);
		} else {
			reg = (qv_info->ceq_idx &
			       I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK) |
			       (I40E_QUEUE_TYPE_PE_CEQ <<
			       I40E_PFINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);
			wr32(hw, reg_idx, reg);

			reg = (I40E_PFINT_CEQCTL_CAUSE_ENA_MASK |
			       (v_idx << I40E_PFINT_CEQCTL_MSIX_INDX_SHIFT) |
			       (qv_info->itr_idx <<
				I40E_PFINT_CEQCTL_ITR_INDX_SHIFT) |
			       (I40E_QUEUE_END_OF_LIST <<
				I40E_PFINT_CEQCTL_NEXTQ_INDX_SHIFT));
			wr32(hw, I40E_PFINT_CEQCTL(qv_info->ceq_idx), reg);
		}
		if (qv_info->aeq_idx != I40E_QUEUE_INVALID_IDX) {
			reg = (I40E_PFINT_AEQCTL_CAUSE_ENA_MASK |
			       (v_idx << I40E_PFINT_AEQCTL_MSIX_INDX_SHIFT) |
			       (qv_info->itr_idx <<
				I40E_PFINT_AEQCTL_ITR_INDX_SHIFT));

			wr32(hw, I40E_PFINT_AEQCTL, reg);
		}
	}
	/* Mitigate sync problems with iwarp VF driver */
	i40e_flush(hw);
	return 0;
err:
	kfree(ldev->qvlist_info);
	ldev->qvlist_info = NULL;
	return -EINVAL;
}