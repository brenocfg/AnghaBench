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
struct reservation_object_list {int dummy; } ;
struct reservation_object {struct reservation_object_list* staged; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reservation_object_add_shared_inplace (struct reservation_object*,struct reservation_object_list*,struct dma_fence*) ; 
 int /*<<< orphan*/  reservation_object_add_shared_replace (struct reservation_object*,struct reservation_object_list*,struct reservation_object_list*,struct dma_fence*) ; 
 struct reservation_object_list* reservation_object_get_list (struct reservation_object*) ; 

void reservation_object_add_shared_fence(struct reservation_object *obj,
					 struct dma_fence *fence)
{
	struct reservation_object_list *old, *fobj = obj->staged;

	old = reservation_object_get_list(obj);
	obj->staged = NULL;

	if (!fobj)
		reservation_object_add_shared_inplace(obj, old, fence);
	else
		reservation_object_add_shared_replace(obj, old, fobj, fence);
}