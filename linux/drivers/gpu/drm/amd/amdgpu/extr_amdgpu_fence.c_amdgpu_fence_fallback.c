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
struct timer_list {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  fallback_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_fence_process (struct amdgpu_ring*) ; 
 TYPE_1__ fence_drv ; 
 struct amdgpu_ring* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct amdgpu_ring* ring ; 

__attribute__((used)) static void amdgpu_fence_fallback(struct timer_list *t)
{
	struct amdgpu_ring *ring = from_timer(ring, t,
					      fence_drv.fallback_timer);

	if (amdgpu_fence_process(ring))
		DRM_WARN("Fence fallback timer expired on ring %s\n", ring->name);
}