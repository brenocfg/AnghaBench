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
struct ion_heap {int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct ion_cma_heap {struct ion_heap heap; struct cma* cma; } ;
struct cma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ion_heap* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ION_HEAP_TYPE_DMA ; 
 int /*<<< orphan*/  ion_cma_ops ; 
 struct ion_cma_heap* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ion_heap *__ion_cma_heap_create(struct cma *cma)
{
	struct ion_cma_heap *cma_heap;

	cma_heap = kzalloc(sizeof(*cma_heap), GFP_KERNEL);

	if (!cma_heap)
		return ERR_PTR(-ENOMEM);

	cma_heap->heap.ops = &ion_cma_ops;
	cma_heap->cma = cma;
	cma_heap->heap.type = ION_HEAP_TYPE_DMA;
	return &cma_heap->heap;
}