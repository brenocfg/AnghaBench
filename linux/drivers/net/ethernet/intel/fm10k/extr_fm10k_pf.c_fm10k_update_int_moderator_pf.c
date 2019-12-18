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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  num_vfs; } ;
struct fm10k_hw {TYPE_1__ iov; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_INT_CTRL ; 
 scalar_t__ FM10K_INT_CTRL_ENABLEMODERATOR ; 
 int /*<<< orphan*/  FM10K_ITR2 (scalar_t__) ; 
 scalar_t__ FM10K_ITR_REG_COUNT_PF ; 
 int /*<<< orphan*/  FM10K_MSIX_VECTOR_MASK (scalar_t__) ; 
 int /*<<< orphan*/  fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fm10k_update_int_moderator_pf(struct fm10k_hw *hw)
{
	u32 i;

	/* Disable interrupt moderator */
	fm10k_write_reg(hw, FM10K_INT_CTRL, 0);

	/* loop through PF from last to first looking enabled vectors */
	for (i = FM10K_ITR_REG_COUNT_PF - 1; i; i--) {
		if (!fm10k_read_reg(hw, FM10K_MSIX_VECTOR_MASK(i)))
			break;
	}

	/* always reset VFITR2[0] to point to last enabled PF vector */
	fm10k_write_reg(hw, FM10K_ITR2(FM10K_ITR_REG_COUNT_PF), i);

	/* reset ITR2[0] to point to last enabled PF vector */
	if (!hw->iov.num_vfs)
		fm10k_write_reg(hw, FM10K_ITR2(0), i);

	/* Enable interrupt moderator */
	fm10k_write_reg(hw, FM10K_INT_CTRL, FM10K_INT_CTRL_ENABLEMODERATOR);
}