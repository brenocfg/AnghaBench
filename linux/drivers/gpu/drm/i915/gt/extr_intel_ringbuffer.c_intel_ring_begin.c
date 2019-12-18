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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring {unsigned int effective_size; unsigned int emit; int size; unsigned int space; int /*<<< orphan*/ * vaddr; } ;
struct i915_request {unsigned int const reserved_space; int /*<<< orphan*/  timeline; struct intel_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int) ; 
 int /*<<< orphan*/  POISON_INUSE ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  memset64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 
 int wait_for_space (struct intel_ring*,int /*<<< orphan*/ ,unsigned int) ; 

u32 *intel_ring_begin(struct i915_request *rq, unsigned int num_dwords)
{
	struct intel_ring *ring = rq->ring;
	const unsigned int remain_usable = ring->effective_size - ring->emit;
	const unsigned int bytes = num_dwords * sizeof(u32);
	unsigned int need_wrap = 0;
	unsigned int total_bytes;
	u32 *cs;

	/* Packets must be qword aligned. */
	GEM_BUG_ON(num_dwords & 1);

	total_bytes = bytes + rq->reserved_space;
	GEM_BUG_ON(total_bytes > ring->effective_size);

	if (unlikely(total_bytes > remain_usable)) {
		const int remain_actual = ring->size - ring->emit;

		if (bytes > remain_usable) {
			/*
			 * Not enough space for the basic request. So need to
			 * flush out the remainder and then wait for
			 * base + reserved.
			 */
			total_bytes += remain_actual;
			need_wrap = remain_actual | 1;
		} else  {
			/*
			 * The base request will fit but the reserved space
			 * falls off the end. So we don't need an immediate
			 * wrap and only need to effectively wait for the
			 * reserved size from the start of ringbuffer.
			 */
			total_bytes = rq->reserved_space + remain_actual;
		}
	}

	if (unlikely(total_bytes > ring->space)) {
		int ret;

		/*
		 * Space is reserved in the ringbuffer for finalising the
		 * request, as that cannot be allowed to fail. During request
		 * finalisation, reserved_space is set to 0 to stop the
		 * overallocation and the assumption is that then we never need
		 * to wait (which has the risk of failing with EINTR).
		 *
		 * See also i915_request_alloc() and i915_request_add().
		 */
		GEM_BUG_ON(!rq->reserved_space);

		ret = wait_for_space(ring, rq->timeline, total_bytes);
		if (unlikely(ret))
			return ERR_PTR(ret);
	}

	if (unlikely(need_wrap)) {
		need_wrap &= ~1;
		GEM_BUG_ON(need_wrap > ring->space);
		GEM_BUG_ON(ring->emit + need_wrap > ring->size);
		GEM_BUG_ON(!IS_ALIGNED(need_wrap, sizeof(u64)));

		/* Fill the tail with MI_NOOP */
		memset64(ring->vaddr + ring->emit, 0, need_wrap / sizeof(u64));
		ring->space -= need_wrap;
		ring->emit = 0;
	}

	GEM_BUG_ON(ring->emit > ring->size - bytes);
	GEM_BUG_ON(ring->space < bytes);
	cs = ring->vaddr + ring->emit;
	GEM_DEBUG_EXEC(memset32(cs, POISON_INUSE, bytes / sizeof(*cs)));
	ring->emit += bytes;
	ring->space -= bytes;

	return cs;
}