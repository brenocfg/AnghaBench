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
struct drm_gem_shmem_object {int /*<<< orphan*/  vmap_lock; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 void* drm_gem_shmem_vmap_locked (struct drm_gem_shmem_object*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

void *drm_gem_shmem_vmap(struct drm_gem_object *obj)
{
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	void *vaddr;
	int ret;

	ret = mutex_lock_interruptible(&shmem->vmap_lock);
	if (ret)
		return ERR_PTR(ret);
	vaddr = drm_gem_shmem_vmap_locked(shmem);
	mutex_unlock(&shmem->vmap_lock);

	return vaddr;
}