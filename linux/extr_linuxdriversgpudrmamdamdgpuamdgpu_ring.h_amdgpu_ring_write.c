#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {scalar_t__ count_dw; size_t buf_mask; int /*<<< orphan*/  ptr_mask; int /*<<< orphan*/  wptr; int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

__attribute__((used)) static inline void amdgpu_ring_write(struct amdgpu_ring *ring, uint32_t v)
{
	if (ring->count_dw <= 0)
		DRM_ERROR("amdgpu: writing more dwords to the ring than expected!\n");
	ring->ring[ring->wptr++ & ring->buf_mask] = v;
	ring->wptr &= ring->ptr_mask;
	ring->count_dw--;
}