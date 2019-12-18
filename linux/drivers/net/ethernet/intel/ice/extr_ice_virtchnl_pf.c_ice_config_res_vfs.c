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
struct ice_vf {int /*<<< orphan*/  num_vf_qs; int /*<<< orphan*/  vf_id; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int num_alloc_vfs; int /*<<< orphan*/  state; TYPE_1__* pdev; int /*<<< orphan*/  num_vf_qps; struct ice_vf* vf; struct ice_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_OICR_INTR_DIS ; 
 int /*<<< orphan*/  __ICE_VF_DIS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ice_check_avail_res (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_cleanup_and_realloc_vf (struct ice_vf*) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_irq_dynamic_ena (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_config_res_vfs(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;
	int v;

	if (ice_check_avail_res(pf)) {
		dev_err(&pf->pdev->dev,
			"Cannot allocate VF resources, try with fewer number of VFs\n");
		return false;
	}

	/* rearm global interrupts */
	if (test_and_clear_bit(__ICE_OICR_INTR_DIS, pf->state))
		ice_irq_dynamic_ena(hw, NULL, NULL);

	/* Finish resetting each VF and allocate resources */
	for (v = 0; v < pf->num_alloc_vfs; v++) {
		struct ice_vf *vf = &pf->vf[v];

		vf->num_vf_qs = pf->num_vf_qps;
		dev_dbg(&pf->pdev->dev,
			"VF-id %d has %d queues configured\n",
			vf->vf_id, vf->num_vf_qs);
		ice_cleanup_and_realloc_vf(vf);
	}

	ice_flush(hw);
	clear_bit(__ICE_VF_DIS, pf->state);

	return true;
}