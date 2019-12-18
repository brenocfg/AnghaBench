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
struct radeon_ring {scalar_t__ count_dw; int /*<<< orphan*/  ring_free_dw; int /*<<< orphan*/  ptr_mask; int /*<<< orphan*/  wptr; int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

__attribute__((used)) static inline void radeon_ring_write(struct radeon_ring *ring, uint32_t v)
{
	if (ring->count_dw <= 0)
		DRM_ERROR("radeon: writing more dwords to the ring than expected!\n");

	ring->ring[ring->wptr++] = v;
	ring->wptr &= ring->ptr_mask;
	ring->count_dw--;
	ring->ring_free_dw--;
}