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
struct reservation_object {int dummy; } ;
struct dma_fence {int dummy; } ;
struct dma_fence_array {struct dma_fence base; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dma_fence_array* dma_fence_array_create (unsigned int,struct dma_fence**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 int /*<<< orphan*/  reservation_object_add_excl_fence (struct reservation_object*,struct dma_fence*) ; 
 int reservation_object_get_fences_rcu (struct reservation_object*,int /*<<< orphan*/ *,unsigned int*,struct dma_fence***) ; 
 int /*<<< orphan*/  reservation_object_get_list (struct reservation_object*) ; 

__attribute__((used)) static int
__reservation_object_make_exclusive(struct reservation_object *obj)
{
	struct dma_fence **fences;
	unsigned int count;
	int r;

	if (!reservation_object_get_list(obj)) /* no shared fences to convert */
		return 0;

	r = reservation_object_get_fences_rcu(obj, NULL, &count, &fences);
	if (r)
		return r;

	if (count == 0) {
		/* Now that was unexpected. */
	} else if (count == 1) {
		reservation_object_add_excl_fence(obj, fences[0]);
		dma_fence_put(fences[0]);
		kfree(fences);
	} else {
		struct dma_fence_array *array;

		array = dma_fence_array_create(count, fences,
					       dma_fence_context_alloc(1), 0,
					       false);
		if (!array)
			goto err_fences_put;

		reservation_object_add_excl_fence(obj, &array->base);
		dma_fence_put(&array->base);
	}

	return 0;

err_fences_put:
	while (count--)
		dma_fence_put(fences[count]);
	kfree(fences);
	return -ENOMEM;
}