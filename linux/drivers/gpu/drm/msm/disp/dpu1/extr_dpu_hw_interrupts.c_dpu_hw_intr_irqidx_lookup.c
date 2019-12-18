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
typedef  scalar_t__ u32 ;
typedef  enum dpu_intr_type { ____Placeholder_dpu_intr_type } dpu_intr_type ;
struct TYPE_3__ {int intr_type; scalar_t__ instance_idx; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* dpu_irq_map ; 
 int /*<<< orphan*/  pr_debug (char*,int,scalar_t__) ; 

__attribute__((used)) static int dpu_hw_intr_irqidx_lookup(enum dpu_intr_type intr_type,
		u32 instance_idx)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dpu_irq_map); i++) {
		if (intr_type == dpu_irq_map[i].intr_type &&
			instance_idx == dpu_irq_map[i].instance_idx)
			return i;
	}

	pr_debug("IRQ lookup fail!! intr_type=%d, instance_idx=%d\n",
			intr_type, instance_idx);
	return -EINVAL;
}