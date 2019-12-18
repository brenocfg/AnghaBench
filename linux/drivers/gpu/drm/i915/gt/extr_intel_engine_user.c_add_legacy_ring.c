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
struct legacy_ring {scalar_t__ class; scalar_t__ instance; TYPE_1__* gt; } ;
struct intel_engine_cs {scalar_t__ class; int legacy_idx; TYPE_1__* gt; } ;
struct TYPE_2__ {struct intel_engine_cs** engine; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct intel_engine_cs**) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int legacy_ring_idx (struct legacy_ring*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void add_legacy_ring(struct legacy_ring *ring,
			    struct intel_engine_cs *engine)
{
	int idx;

	if (engine->gt != ring->gt || engine->class != ring->class) {
		ring->gt = engine->gt;
		ring->class = engine->class;
		ring->instance = 0;
	}

	idx = legacy_ring_idx(ring);
	if (unlikely(idx == -1))
		return;

	GEM_BUG_ON(idx >= ARRAY_SIZE(ring->gt->engine));
	ring->gt->engine[idx] = engine;
	ring->instance++;

	engine->legacy_idx = idx;
}