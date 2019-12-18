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
struct vnic_intr {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_credits; int /*<<< orphan*/  mask_on_assertion; int /*<<< orphan*/  coalescing_type; int /*<<< orphan*/  coalescing_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ *) ; 

void svnic_intr_init(struct vnic_intr *intr, unsigned int coalescing_timer,
	unsigned int coalescing_type, unsigned int mask_on_assertion)
{
	iowrite32(coalescing_timer, &intr->ctrl->coalescing_timer);
	iowrite32(coalescing_type, &intr->ctrl->coalescing_type);
	iowrite32(mask_on_assertion, &intr->ctrl->mask_on_assertion);
	iowrite32(0, &intr->ctrl->int_credits);
}