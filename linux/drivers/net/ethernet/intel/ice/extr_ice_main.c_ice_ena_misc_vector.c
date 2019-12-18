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
struct ice_hw {int dummy; } ;
struct ice_pf {int /*<<< orphan*/  oicr_idx; struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int /*<<< orphan*/ ) ; 
 int GLINT_DYN_CTL_INTENA_MSK_M ; 
 int GLINT_DYN_CTL_SW_ITR_INDX_M ; 
 int /*<<< orphan*/  PFINT_OICR ; 
 int PFINT_OICR_ECC_ERR_M ; 
 int /*<<< orphan*/  PFINT_OICR_ENA ; 
 int PFINT_OICR_GRST_M ; 
 int PFINT_OICR_HMC_ERR_M ; 
 int PFINT_OICR_MAL_DETECT_M ; 
 int PFINT_OICR_PCI_EXCEPTION_M ; 
 int PFINT_OICR_PE_CRITERR_M ; 
 int PFINT_OICR_VFLR_M ; 
 int /*<<< orphan*/  rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ice_ena_misc_vector(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;
	u32 val;

	/* clear things first */
	wr32(hw, PFINT_OICR_ENA, 0);	/* disable all */
	rd32(hw, PFINT_OICR);		/* read to clear */

	val = (PFINT_OICR_ECC_ERR_M |
	       PFINT_OICR_MAL_DETECT_M |
	       PFINT_OICR_GRST_M |
	       PFINT_OICR_PCI_EXCEPTION_M |
	       PFINT_OICR_VFLR_M |
	       PFINT_OICR_HMC_ERR_M |
	       PFINT_OICR_PE_CRITERR_M);

	wr32(hw, PFINT_OICR_ENA, val);

	/* SW_ITR_IDX = 0, but don't change INTENA */
	wr32(hw, GLINT_DYN_CTL(pf->oicr_idx),
	     GLINT_DYN_CTL_SW_ITR_INDX_M | GLINT_DYN_CTL_INTENA_MSK_M);
}