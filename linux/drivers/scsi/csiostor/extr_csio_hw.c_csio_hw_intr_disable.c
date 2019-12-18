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
struct csio_hw {int flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int CSIO_HWF_HW_INTR_ENABLED ; 
 int CSIO_HW_CHIP_MASK ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_INT_MAP0_A ; 
 int /*<<< orphan*/  PL_PF_INT_ENABLE_A ; 
 int /*<<< orphan*/  PL_WHOAMI_A ; 
 int SOURCEPF_G (int /*<<< orphan*/ ) ; 
 int T6_SOURCEPF_G (int /*<<< orphan*/ ) ; 
 scalar_t__ csio_is_hw_master (struct csio_hw*) ; 
 scalar_t__ csio_is_t5 (int) ; 
 int /*<<< orphan*/  csio_mb_intr_disable (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_reg_field (struct csio_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
csio_hw_intr_disable(struct csio_hw *hw)
{
	u32 pf = 0;

	if (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		pf = SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));
	else
		pf = T6_SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));

	if (!(hw->flags & CSIO_HWF_HW_INTR_ENABLED))
		return;

	hw->flags &= ~CSIO_HWF_HW_INTR_ENABLED;

	csio_wr_reg32(hw, 0, MYPF_REG(PL_PF_INT_ENABLE_A));
	if (csio_is_hw_master(hw))
		csio_set_reg_field(hw, PL_INT_MAP0_A, 1 << pf, 0);

	/* Turn off MB interrupts */
	csio_mb_intr_disable(hw);

}