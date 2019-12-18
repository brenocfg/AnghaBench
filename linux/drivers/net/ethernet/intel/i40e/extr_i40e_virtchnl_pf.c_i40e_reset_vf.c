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
struct i40e_vf {size_t lan_vsi_idx; int /*<<< orphan*/  vf_id; struct i40e_pf* pf; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int /*<<< orphan*/  state; int /*<<< orphan*/ * vsi; TYPE_1__* pdev; struct i40e_hw hw; } ;
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
 int /*<<< orphan*/  i40e_vsi_stop_rings (int /*<<< orphan*/ ) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

bool i40e_reset_vf(struct i40e_vf *vf, bool flr)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	bool rsd = false;
	u32 reg;
	int i;

	/* If the VFs have been disabled, this means something else is
	 * resetting the VF, so we shouldn't continue.
	 */
	if (test_and_set_bit(__I40E_VF_DISABLE, pf->state))
		return false;

	i40e_trigger_vf_reset(vf, flr);

	/* poll VPGEN_VFRSTAT reg to make sure
	 * that reset is complete
	 */
	for (i = 0; i < 10; i++) {
		/* VF reset requires driver to first reset the VF and then
		 * poll the status register to make sure that the reset
		 * completed successfully. Due to internal HW FIFO flushes,
		 * we must wait 10ms before the register will be valid.
		 */
		usleep_range(10000, 20000);
		reg = rd32(hw, I40E_VPGEN_VFRSTAT(vf->vf_id));
		if (reg & I40E_VPGEN_VFRSTAT_VFRD_MASK) {
			rsd = true;
			break;
		}
	}

	if (flr)
		usleep_range(10000, 20000);

	if (!rsd)
		dev_err(&pf->pdev->dev, "VF reset check timeout on VF %d\n",
			vf->vf_id);
	usleep_range(10000, 20000);

	/* On initial reset, we don't have any queues to disable */
	if (vf->lan_vsi_idx != 0)
		i40e_vsi_stop_rings(pf->vsi[vf->lan_vsi_idx]);

	i40e_cleanup_reset_vf(vf);

	i40e_flush(hw);
	clear_bit(__I40E_VF_DISABLE, pf->state);

	return true;
}