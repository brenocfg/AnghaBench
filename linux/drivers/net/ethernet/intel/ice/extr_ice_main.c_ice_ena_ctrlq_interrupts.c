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
typedef  int u16 ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFINT_FW_CTL ; 
 int PFINT_FW_CTL_CAUSE_ENA_M ; 
 int PFINT_FW_CTL_MSIX_INDX_M ; 
 int /*<<< orphan*/  PFINT_MBX_CTL ; 
 int PFINT_MBX_CTL_CAUSE_ENA_M ; 
 int PFINT_MBX_CTL_MSIX_INDX_M ; 
 int /*<<< orphan*/  PFINT_OICR_CTL ; 
 int PFINT_OICR_CTL_CAUSE_ENA_M ; 
 int PFINT_OICR_CTL_MSIX_INDX_M ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ice_ena_ctrlq_interrupts(struct ice_hw *hw, u16 reg_idx)
{
	u32 val;

	val = ((reg_idx & PFINT_OICR_CTL_MSIX_INDX_M) |
	       PFINT_OICR_CTL_CAUSE_ENA_M);
	wr32(hw, PFINT_OICR_CTL, val);

	/* enable Admin queue Interrupt causes */
	val = ((reg_idx & PFINT_FW_CTL_MSIX_INDX_M) |
	       PFINT_FW_CTL_CAUSE_ENA_M);
	wr32(hw, PFINT_FW_CTL, val);

	/* enable Mailbox queue Interrupt causes */
	val = ((reg_idx & PFINT_MBX_CTL_MSIX_INDX_M) |
	       PFINT_MBX_CTL_CAUSE_ENA_M);
	wr32(hw, PFINT_MBX_CTL, val);

	ice_flush(hw);
}