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
 int /*<<< orphan*/  drm_gem_shmem_vunmap_locked (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

void drm_gem_shmem_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	mutex_lock(&shmem->vmap_lock);
	drm_gem_shmem_vunmap_locked(shmem);
	mutex_unlock(&shmem->vmap_lock);
}