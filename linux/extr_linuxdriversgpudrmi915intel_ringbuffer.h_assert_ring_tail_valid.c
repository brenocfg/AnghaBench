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
struct intel_ring {unsigned int head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE_BYTES ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  intel_ring_offset_valid (struct intel_ring const*,unsigned int) ; 
 scalar_t__ round_down (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
assert_ring_tail_valid(const struct intel_ring *ring, unsigned int tail)
{
	GEM_BUG_ON(!intel_ring_offset_valid(ring, tail));

	/*
	 * "Ring Buffer Use"
	 *	Gen2 BSpec "1. Programming Environment" / 1.4.4.6
	 *	Gen3 BSpec "1c Memory Interface Functions" / 2.3.4.5
	 *	Gen4+ BSpec "1c Memory Interface and Command Stream" / 5.3.4.5
	 * "If the Ring Buffer Head Pointer and the Tail Pointer are on the
	 * same cacheline, the Head Pointer must not be greater than the Tail
	 * Pointer."
	 *
	 * We use ring->head as the last known location of the actual RING_HEAD,
	 * it may have advanced but in the worst case it is equally the same
	 * as ring->head and so we should never program RING_TAIL to advance
	 * into the same cacheline as ring->head.
	 */
#define cacheline(a) round_down(a, CACHELINE_BYTES)
	GEM_BUG_ON(cacheline(tail) == cacheline(ring->head) &&
		   tail < ring->head);
#undef cacheline
}