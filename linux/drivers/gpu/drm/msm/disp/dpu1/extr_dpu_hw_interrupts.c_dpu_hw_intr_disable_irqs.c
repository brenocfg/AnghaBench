#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dpu_hw_intr {int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  en_off; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 TYPE_1__* dpu_intr_set ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int dpu_hw_intr_disable_irqs(struct dpu_hw_intr *intr)
{
	int i;

	if (!intr)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(dpu_intr_set); i++)
		DPU_REG_WRITE(&intr->hw, dpu_intr_set[i].en_off, 0x00000000);

	/* ensure register writes go through */
	wmb();

	return 0;
}