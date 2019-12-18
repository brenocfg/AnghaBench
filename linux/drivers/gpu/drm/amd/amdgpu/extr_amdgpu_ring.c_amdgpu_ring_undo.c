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
struct amdgpu_ring {TYPE_1__* funcs; int /*<<< orphan*/  wptr_old; int /*<<< orphan*/  wptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* end_use ) (struct amdgpu_ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*) ; 

void amdgpu_ring_undo(struct amdgpu_ring *ring)
{
	ring->wptr = ring->wptr_old;

	if (ring->funcs->end_use)
		ring->funcs->end_use(ring);
}