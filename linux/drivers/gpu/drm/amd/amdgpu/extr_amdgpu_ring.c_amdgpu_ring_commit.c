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
typedef  int uint32_t ;
struct amdgpu_ring {int wptr; TYPE_1__* funcs; } ;
struct TYPE_2__ {int align_mask; int /*<<< orphan*/  (* end_use ) (struct amdgpu_ring*) ;int /*<<< orphan*/  (* insert_nop ) (struct amdgpu_ring*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ring_set_wptr (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_ring*) ; 

void amdgpu_ring_commit(struct amdgpu_ring *ring)
{
	uint32_t count;

	/* We pad to match fetch size */
	count = ring->funcs->align_mask + 1 -
		(ring->wptr & ring->funcs->align_mask);
	count %= ring->funcs->align_mask + 1;
	ring->funcs->insert_nop(ring, count);

	mb();
	amdgpu_ring_set_wptr(ring);

	if (ring->funcs->end_use)
		ring->funcs->end_use(ring);
}