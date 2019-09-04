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
struct amdgpu_ring {unsigned int max_dw; unsigned int count_dw; TYPE_1__* funcs; int /*<<< orphan*/  wptr; int /*<<< orphan*/  wptr_old; } ;
struct TYPE_2__ {unsigned int align_mask; int /*<<< orphan*/  (* begin_use ) (struct amdgpu_ring*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*) ; 

int amdgpu_ring_alloc(struct amdgpu_ring *ring, unsigned ndw)
{
	/* Align requested size with padding so unlock_commit can
	 * pad safely */
	ndw = (ndw + ring->funcs->align_mask) & ~ring->funcs->align_mask;

	/* Make sure we aren't trying to allocate more space
	 * than the maximum for one submission
	 */
	if (WARN_ON_ONCE(ndw > ring->max_dw))
		return -ENOMEM;

	ring->count_dw = ndw;
	ring->wptr_old = ring->wptr;

	if (ring->funcs->begin_use)
		ring->funcs->begin_use(ring);

	return 0;
}