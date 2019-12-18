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
typedef  scalar_t__ u16 ;
struct ice_res_tracker {int num_entries; int end; } ;
struct TYPE_4__ {scalar_t__ num_msix_vectors; } ;
struct TYPE_5__ {TYPE_1__ common_cap; } ;
struct TYPE_6__ {TYPE_2__ func_caps; } ;
struct ice_pf {int sriov_base_vector; int /*<<< orphan*/  num_avail_sw_msix; struct ice_res_tracker* irq_tracker; TYPE_3__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int ice_get_max_valid_res_idx (struct ice_res_tracker*) ; 

__attribute__((used)) static int ice_sriov_set_msix_res(struct ice_pf *pf, u16 num_msix_needed)
{
	int max_valid_res_idx = ice_get_max_valid_res_idx(pf->irq_tracker);
	u16 pf_total_msix_vectors =
		pf->hw.func_caps.common_cap.num_msix_vectors;
	struct ice_res_tracker *res = pf->irq_tracker;
	int sriov_base_vector;

	if (max_valid_res_idx < 0)
		return max_valid_res_idx;

	sriov_base_vector = pf_total_msix_vectors - num_msix_needed;

	/* make sure we only grab irq_tracker entries from the list end and
	 * that we have enough available MSIX vectors
	 */
	if (sriov_base_vector <= max_valid_res_idx)
		return -EINVAL;

	pf->sriov_base_vector = sriov_base_vector;

	/* dip into irq_tracker entries and update used resources */
	if (num_msix_needed > (pf_total_msix_vectors - res->num_entries)) {
		pf->num_avail_sw_msix -=
			res->num_entries - pf->sriov_base_vector;
		res->end = pf->sriov_base_vector;
	}

	return 0;
}