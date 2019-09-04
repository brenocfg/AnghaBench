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
struct intel_ring {unsigned long size; unsigned long effective_size; int /*<<< orphan*/  request_list; int /*<<< orphan*/ * timeline; void* vaddr; } ;
struct mock_ring {struct intel_ring base; int /*<<< orphan*/  timeline; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long const MIN_SPACE_FOR_ADD_REQUEST ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  i915_timeline_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_update_space (struct intel_ring*) ; 
 struct mock_ring* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_ring *mock_ring(struct intel_engine_cs *engine)
{
	const unsigned long sz = PAGE_SIZE / 2;
	struct mock_ring *ring;

	BUILD_BUG_ON(MIN_SPACE_FOR_ADD_REQUEST > sz);

	ring = kzalloc(sizeof(*ring) + sz, GFP_KERNEL);
	if (!ring)
		return NULL;

	i915_timeline_init(engine->i915, &ring->timeline, engine->name);

	ring->base.size = sz;
	ring->base.effective_size = sz;
	ring->base.vaddr = (void *)(ring + 1);
	ring->base.timeline = &ring->timeline;

	INIT_LIST_HEAD(&ring->base.request_list);
	intel_ring_update_space(&ring->base);

	return &ring->base;
}