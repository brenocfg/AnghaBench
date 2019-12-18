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
struct drm_gem_shmem_object {int /*<<< orphan*/  pages_lock; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_shmem_purge_locked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_mmu_unmap (int /*<<< orphan*/ ) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  to_panfrost_bo (struct drm_gem_object*) ; 

__attribute__((used)) static bool panfrost_gem_purge(struct drm_gem_object *obj)
{
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	if (!mutex_trylock(&shmem->pages_lock))
		return false;

	panfrost_mmu_unmap(to_panfrost_bo(obj));
	drm_gem_shmem_purge_locked(obj);

	mutex_unlock(&shmem->pages_lock);
	return true;
}