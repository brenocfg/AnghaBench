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
struct TYPE_2__ {unsigned int ring_size; int ptr_mask; scalar_t__ rptr; } ;
struct radeon_device {TYPE_1__ ih; } ;

/* Variables and functions */
 int order_base_2 (unsigned int) ; 

void r600_ih_ring_init(struct radeon_device *rdev, unsigned ring_size)
{
	u32 rb_bufsz;

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 4);
	ring_size = (1 << rb_bufsz) * 4;
	rdev->ih.ring_size = ring_size;
	rdev->ih.ptr_mask = rdev->ih.ring_size - 1;
	rdev->ih.rptr = 0;
}