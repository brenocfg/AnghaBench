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
struct intel_ring {unsigned int tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_ring_tail_valid (struct intel_ring*,unsigned int) ; 

__attribute__((used)) static inline unsigned int
intel_ring_set_tail(struct intel_ring *ring, unsigned int tail)
{
	/* Whilst writes to the tail are strictly order, there is no
	 * serialisation between readers and the writers. The tail may be
	 * read by i915_request_retire() just as it is being updated
	 * by execlists, as although the breadcrumb is complete, the context
	 * switch hasn't been seen.
	 */
	assert_ring_tail_valid(ring, tail);
	ring->tail = tail;
	return tail;
}