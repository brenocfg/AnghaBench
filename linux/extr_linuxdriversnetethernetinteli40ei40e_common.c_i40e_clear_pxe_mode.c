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
typedef  int u32 ;
struct i40e_hw {scalar_t__ revision_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GLLAN_RCTL_0 ; 
 int I40E_GLLAN_RCTL_0_PXE_MODE_MASK ; 
 int /*<<< orphan*/  i40e_aq_clear_pxe_mode (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_check_asq_alive (struct i40e_hw*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void i40e_clear_pxe_mode(struct i40e_hw *hw)
{
	u32 reg;

	if (i40e_check_asq_alive(hw))
		i40e_aq_clear_pxe_mode(hw, NULL);

	/* Clear single descriptor fetch/write-back mode */
	reg = rd32(hw, I40E_GLLAN_RCTL_0);

	if (hw->revision_id == 0) {
		/* As a work around clear PXE_MODE instead of setting it */
		wr32(hw, I40E_GLLAN_RCTL_0, (reg & (~I40E_GLLAN_RCTL_0_PXE_MODE_MASK)));
	} else {
		wr32(hw, I40E_GLLAN_RCTL_0, (reg | I40E_GLLAN_RCTL_0_PXE_MODE_MASK));
	}
}