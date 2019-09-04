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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpu_hw_intr {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dpu_hw_intr_set_mask(struct dpu_hw_intr *intr, uint32_t reg_off,
		uint32_t mask)
{
	if (!intr)
		return;

	DPU_REG_WRITE(&intr->hw, reg_off, mask);

	/* ensure register writes go through */
	wmb();
}