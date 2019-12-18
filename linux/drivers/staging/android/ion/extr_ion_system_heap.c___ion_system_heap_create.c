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
struct ion_heap {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct ion_system_heap {struct ion_heap heap; int /*<<< orphan*/  pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ion_heap* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ION_HEAP_FLAG_DEFER_FREE ; 
 int /*<<< orphan*/  ION_HEAP_TYPE_SYSTEM ; 
 scalar_t__ ion_system_heap_create_pools (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ion_system_heap*) ; 
 struct ion_system_heap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_heap_ops ; 

__attribute__((used)) static struct ion_heap *__ion_system_heap_create(void)
{
	struct ion_system_heap *heap;

	heap = kzalloc(sizeof(*heap), GFP_KERNEL);
	if (!heap)
		return ERR_PTR(-ENOMEM);
	heap->heap.ops = &system_heap_ops;
	heap->heap.type = ION_HEAP_TYPE_SYSTEM;
	heap->heap.flags = ION_HEAP_FLAG_DEFER_FREE;

	if (ion_system_heap_create_pools(heap->pools))
		goto free_heap;

	return &heap->heap;

free_heap:
	kfree(heap);
	return ERR_PTR(-ENOMEM);
}