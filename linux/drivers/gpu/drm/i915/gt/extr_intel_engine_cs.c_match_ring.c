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
typedef  scalar_t__ u32 ;
struct i915_request {TYPE_1__* ring; int /*<<< orphan*/  engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 scalar_t__ ENGINE_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_START ; 
 scalar_t__ i915_ggtt_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool match_ring(struct i915_request *rq)
{
	u32 ring = ENGINE_READ(rq->engine, RING_START);

	return ring == i915_ggtt_offset(rq->ring->vma);
}