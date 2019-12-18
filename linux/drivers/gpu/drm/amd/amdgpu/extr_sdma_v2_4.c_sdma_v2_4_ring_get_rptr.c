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
typedef  int uint64_t ;
struct amdgpu_ring {size_t rptr_offs; TYPE_2__* adev; } ;
struct TYPE_3__ {int* wb; } ;
struct TYPE_4__ {TYPE_1__ wb; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t sdma_v2_4_ring_get_rptr(struct amdgpu_ring *ring)
{
	/* XXX check if swapping is necessary on BE */
	return ring->adev->wb.wb[ring->rptr_offs] >> 2;
}