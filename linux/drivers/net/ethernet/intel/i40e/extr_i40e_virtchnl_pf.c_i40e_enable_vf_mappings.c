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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_vf {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  lan_vsi_id; struct i40e_pf* pf; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VPLAN_MAPENA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VPLAN_MAPENA_TXRX_ENA_MASK ; 
 int /*<<< orphan*/  I40E_VSILAN_QBASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VSILAN_QBASE_VSIQTABLE_ENA_MASK ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_map_pf_queues_to_vsi (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_map_pf_to_vf_queues (struct i40e_vf*) ; 
 int /*<<< orphan*/  i40e_write_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_enable_vf_mappings(struct i40e_vf *vf)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	u32 reg;

	/* Tell the hardware we're using noncontiguous mapping. HW requires
	 * that VF queues be mapped using this method, even when they are
	 * contiguous in real life
	 */
	i40e_write_rx_ctl(hw, I40E_VSILAN_QBASE(vf->lan_vsi_id),
			  I40E_VSILAN_QBASE_VSIQTABLE_ENA_MASK);

	/* enable VF vplan_qtable mappings */
	reg = I40E_VPLAN_MAPENA_TXRX_ENA_MASK;
	wr32(hw, I40E_VPLAN_MAPENA(vf->vf_id), reg);

	i40e_map_pf_to_vf_queues(vf);
	i40e_map_pf_queues_to_vsi(vf);

	i40e_flush(hw);
}