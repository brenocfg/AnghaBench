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
typedef  int u32 ;
struct i40e_vf {size_t lan_vsi_idx; int /*<<< orphan*/  vf_id; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int num_alloc_vfs; int /*<<< orphan*/  state; struct i40e_vf* vf; int /*<<< orphan*/ * vsi; TYPE_1__* pdev; struct i40e_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VPGEN_VFRSTAT (int /*<<< orphan*/ ) ; 
 int I40E_VPGEN_VFRSTAT_VFRD_MASK ; 
 int /*<<< orphan*/  __I40E_VF_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_cleanup_reset_vf (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_trigger_vf_reset (struct i40e_vf*,int) ; 
 int /*<<< orphan*/  i40e_vsi_stop_rings_no_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vsi_wait_queues_disabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

bool i40e_reset_all_vfs(struct i40e_pf *pf, bool flr)
{
	struct i40e_hw *hw = &pf->hw;
	struct i40e_vf *vf;
	int i, v;
	u32 reg;

	/* If we don't have any VFs, then there is nothing to reset */
	if (!pf->num_alloc_vfs)
		return false;

	/* If VFs have been disabled, there is no need to reset */
	if (test_and_set_bit(__I40E_VF_DISABLE, pf->state))
		return false;

	/* Begin reset on all VFs at once */
	for (v = 0; v < pf->num_alloc_vfs; v++)
		i40e_trigger_vf_reset(&pf->vf[v], flr);

	/* HW requires some time to make sure it can flush the FIFO for a VF
	 * when it resets it. Poll the VPGEN_VFRSTAT register for each VF in
	 * sequence to make sure that it has completed. We'll keep track of
	 * the VFs using a simple iterator that increments once that VF has
	 * finished resetting.
	 */
	for (i = 0, v = 0; i < 10 && v < pf->num_alloc_vfs; i++) {
		usleep_range(10000, 20000);

		/* Check each VF in sequence, beginning with the VF to fail
		 * the previous check.
		 */
		while (v < pf->num_alloc_vfs) {
			vf = &pf->vf[v];
			reg = rd32(hw, I40E_VPGEN_VFRSTAT(vf->vf_id));
			if (!(reg & I40E_VPGEN_VFRSTAT_VFRD_MASK))
				break;

			/* If the current VF has finished resetting, move on
			 * to the next VF in sequence.
			 */
			v++;
		}
	}

	if (flr)
		usleep_range(10000, 20000);

	/* Display a warning if at least one VF didn't manage to reset in
	 * time, but continue on with the operation.
	 */
	if (v < pf->num_alloc_vfs)
		dev_err(&pf->pdev->dev, "VF reset check timeout on VF %d\n",
			pf->vf[v].vf_id);
	usleep_range(10000, 20000);

	/* Begin disabling all the rings associated with VFs, but do not wait
	 * between each VF.
	 */
	for (v = 0; v < pf->num_alloc_vfs; v++) {
		/* On initial reset, we don't have any queues to disable */
		if (pf->vf[v].lan_vsi_idx == 0)
			continue;

		i40e_vsi_stop_rings_no_wait(pf->vsi[pf->vf[v].lan_vsi_idx]);
	}

	/* Now that we've notified HW to disable all of the VF rings, wait
	 * until they finish.
	 */
	for (v = 0; v < pf->num_alloc_vfs; v++) {
		/* On initial reset, we don't have any queues to disable */
		if (pf->vf[v].lan_vsi_idx == 0)
			continue;

		i40e_vsi_wait_queues_disabled(pf->vsi[pf->vf[v].lan_vsi_idx]);
	}

	/* Hw may need up to 50ms to finish disabling the RX queues. We
	 * minimize the wait by delaying only once for all VFs.
	 */
	mdelay(50);

	/* Finish the reset on each VF */
	for (v = 0; v < pf->num_alloc_vfs; v++)
		i40e_cleanup_reset_vf(&pf->vf[v]);

	i40e_flush(hw);
	clear_bit(__I40E_VF_DISABLE, pf->state);

	return true;
}