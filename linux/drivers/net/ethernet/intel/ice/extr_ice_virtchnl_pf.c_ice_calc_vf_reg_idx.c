#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ice_vf {int vf_id; struct ice_pf* pf; } ;
struct ice_q_vector {int v_idx; } ;
struct ice_pf {int sriov_base_vector; int num_vf_msix; } ;

/* Variables and functions */
 int EINVAL ; 

int ice_calc_vf_reg_idx(struct ice_vf *vf, struct ice_q_vector *q_vector)
{
	struct ice_pf *pf;

	if (!vf || !q_vector)
		return -EINVAL;

	pf = vf->pf;

	/* always add one to account for the OICR being the first MSIX */
	return pf->sriov_base_vector + pf->num_vf_msix * vf->vf_id +
		q_vector->v_idx + 1;
}