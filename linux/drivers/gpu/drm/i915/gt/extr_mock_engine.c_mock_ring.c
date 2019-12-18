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
struct intel_ring {unsigned long size; unsigned long effective_size; int /*<<< orphan*/  pin_count; void* vaddr; int /*<<< orphan*/  ref; } ;
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_ring_update_space (struct intel_ring*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct intel_ring* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_ring *mock_ring(struct intel_engine_cs *engine)
{
	const unsigned long sz = PAGE_SIZE / 2;
	struct intel_ring *ring;

	ring = kzalloc(sizeof(*ring) + sz, GFP_KERNEL);
	if (!ring)
		return NULL;

	kref_init(&ring->ref);
	ring->size = sz;
	ring->effective_size = sz;
	ring->vaddr = (void *)(ring + 1);
	atomic_set(&ring->pin_count, 1);

	intel_ring_update_space(ring);

	return ring;
}