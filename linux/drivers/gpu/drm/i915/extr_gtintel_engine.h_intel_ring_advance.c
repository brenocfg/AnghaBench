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
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {TYPE_1__* ring; } ;
struct TYPE_2__ {int emit; int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 

__attribute__((used)) static inline void intel_ring_advance(struct i915_request *rq, u32 *cs)
{
	/* Dummy function.
	 *
	 * This serves as a placeholder in the code so that the reader
	 * can compare against the preceding intel_ring_begin() and
	 * check that the number of dwords emitted matches the space
	 * reserved for the command packet (i.e. the value passed to
	 * intel_ring_begin()).
	 */
	GEM_BUG_ON((rq->ring->vaddr + rq->ring->emit) != cs);
}