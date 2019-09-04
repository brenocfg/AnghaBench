#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct kfd_dev {TYPE_2__* device_info; } ;
struct TYPE_4__ {TYPE_1__* event_interrupt_class; } ;
struct TYPE_3__ {unsigned int (* interrupt_isr ) (struct kfd_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 unsigned int stub1 (struct kfd_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 

bool interrupt_is_wanted(struct kfd_dev *dev,
			const uint32_t *ih_ring_entry,
			uint32_t *patched_ihre, bool *flag)
{
	/* integer and bitwise OR so there is no boolean short-circuiting */
	unsigned int wanted = 0;

	wanted |= dev->device_info->event_interrupt_class->interrupt_isr(dev,
					 ih_ring_entry, patched_ihre, flag);

	return wanted != 0;
}