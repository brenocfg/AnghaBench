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
struct intel_ring {unsigned int effective_size; unsigned int emit; unsigned int size; unsigned int space; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ unlikely (int) ; 
 int wait_for_space (struct intel_ring*,unsigned int) ; 

int intel_ring_wait_for_space(struct intel_ring *ring, unsigned int bytes)
{
	GEM_BUG_ON(bytes > ring->effective_size);
	if (unlikely(bytes > ring->effective_size - ring->emit))
		bytes += ring->size - ring->emit;

	if (unlikely(bytes > ring->space)) {
		int ret = wait_for_space(ring, bytes);
		if (unlikely(ret))
			return ret;
	}

	GEM_BUG_ON(ring->space < bytes);
	return 0;
}