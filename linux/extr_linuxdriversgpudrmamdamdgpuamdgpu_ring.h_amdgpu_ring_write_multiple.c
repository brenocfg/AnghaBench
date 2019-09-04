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
struct amdgpu_ring {int count_dw; unsigned int wptr; unsigned int buf_mask; int ptr_mask; int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void amdgpu_ring_write_multiple(struct amdgpu_ring *ring,
					      void *src, int count_dw)
{
	unsigned occupied, chunk1, chunk2;
	void *dst;

	if (unlikely(ring->count_dw < count_dw))
		DRM_ERROR("amdgpu: writing more dwords to the ring than expected!\n");

	occupied = ring->wptr & ring->buf_mask;
	dst = (void *)&ring->ring[occupied];
	chunk1 = ring->buf_mask + 1 - occupied;
	chunk1 = (chunk1 >= count_dw) ? count_dw: chunk1;
	chunk2 = count_dw - chunk1;
	chunk1 <<= 2;
	chunk2 <<= 2;

	if (chunk1)
		memcpy(dst, src, chunk1);

	if (chunk2) {
		src += chunk1;
		dst = (void *)ring->ring;
		memcpy(dst, src, chunk2);
	}

	ring->wptr += count_dw;
	ring->wptr &= ring->ptr_mask;
	ring->count_dw -= count_dw;
}