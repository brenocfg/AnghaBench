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
typedef  int /*<<< orphan*/  u64 ;
struct amdgpu_ring {size_t wptr_offs; TYPE_2__* adev; scalar_t__ use_doorbell; } ;
typedef  int /*<<< orphan*/  atomic64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * wb; } ;
struct TYPE_4__ {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 gfx_v9_0_ring_get_wptr_compute(struct amdgpu_ring *ring)
{
	u64 wptr;

	/* XXX check if swapping is necessary on BE */
	if (ring->use_doorbell)
		wptr = atomic64_read((atomic64_t *)&ring->adev->wb.wb[ring->wptr_offs]);
	else
		BUG();
	return wptr;
}