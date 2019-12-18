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
typedef  scalar_t__ u16 ;
struct ice_vsi {scalar_t__ type; int /*<<< orphan*/  base_vector; int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  idx; scalar_t__ num_q_vectors; struct ice_pf* back; } ;
struct ice_pf {int /*<<< orphan*/  num_avail_sw_msix; TYPE_1__* pdev; int /*<<< orphan*/  irq_tracker; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 scalar_t__ ICE_VSI_VF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_get_res (struct ice_pf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_setup_vector_base(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	u16 num_q_vectors;

	/* SRIOV doesn't grab irq_tracker entries for each VSI */
	if (vsi->type == ICE_VSI_VF)
		return 0;

	if (vsi->base_vector) {
		dev_dbg(&pf->pdev->dev, "VSI %d has non-zero base vector %d\n",
			vsi->vsi_num, vsi->base_vector);
		return -EEXIST;
	}

	num_q_vectors = vsi->num_q_vectors;
	/* reserve slots from OS requested IRQs */
	vsi->base_vector = ice_get_res(pf, pf->irq_tracker, num_q_vectors,
				       vsi->idx);
	if (vsi->base_vector < 0) {
		dev_err(&pf->pdev->dev,
			"Failed to get tracking for %d vectors for VSI %d, err=%d\n",
			num_q_vectors, vsi->vsi_num, vsi->base_vector);
		return -ENOENT;
	}
	pf->num_avail_sw_msix -= num_q_vectors;

	return 0;
}