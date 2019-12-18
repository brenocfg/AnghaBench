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
struct etnaviv_gem_object {void* vaddr; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_2__ {void* (* vmap ) (struct etnaviv_gem_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* stub1 (struct etnaviv_gem_object*) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 

void *etnaviv_gem_vmap(struct drm_gem_object *obj)
{
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	if (etnaviv_obj->vaddr)
		return etnaviv_obj->vaddr;

	mutex_lock(&etnaviv_obj->lock);
	/*
	 * Need to check again, as we might have raced with another thread
	 * while waiting for the mutex.
	 */
	if (!etnaviv_obj->vaddr)
		etnaviv_obj->vaddr = etnaviv_obj->ops->vmap(etnaviv_obj);
	mutex_unlock(&etnaviv_obj->lock);

	return etnaviv_obj->vaddr;
}