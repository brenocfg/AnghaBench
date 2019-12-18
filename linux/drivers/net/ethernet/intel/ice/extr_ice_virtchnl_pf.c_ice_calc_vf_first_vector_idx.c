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
struct ice_vf {int vf_id; } ;
struct ice_pf {int sriov_base_vector; int num_vf_msix; } ;

/* Variables and functions */

__attribute__((used)) static int ice_calc_vf_first_vector_idx(struct ice_pf *pf, struct ice_vf *vf)
{
	return pf->sriov_base_vector + vf->vf_id * pf->num_vf_msix;
}