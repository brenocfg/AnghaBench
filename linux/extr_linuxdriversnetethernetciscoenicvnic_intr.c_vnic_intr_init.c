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
typedef  int /*<<< orphan*/  u32 ;
struct vnic_intr {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_credits; int /*<<< orphan*/  mask_on_assertion; int /*<<< orphan*/  coalescing_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_coalescing_timer_set (struct vnic_intr*,int /*<<< orphan*/ ) ; 

void vnic_intr_init(struct vnic_intr *intr, u32 coalescing_timer,
	unsigned int coalescing_type, unsigned int mask_on_assertion)
{
	vnic_intr_coalescing_timer_set(intr, coalescing_timer);
	iowrite32(coalescing_type, &intr->ctrl->coalescing_type);
	iowrite32(mask_on_assertion, &intr->ctrl->mask_on_assertion);
	iowrite32(0, &intr->ctrl->int_credits);
}