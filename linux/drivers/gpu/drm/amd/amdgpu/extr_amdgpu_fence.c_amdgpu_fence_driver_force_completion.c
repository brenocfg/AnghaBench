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
struct TYPE_2__ {int /*<<< orphan*/  sync_seq; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_fence_process (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_fence_write (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 

void amdgpu_fence_driver_force_completion(struct amdgpu_ring *ring)
{
	amdgpu_fence_write(ring, ring->fence_drv.sync_seq);
	amdgpu_fence_process(ring);
}