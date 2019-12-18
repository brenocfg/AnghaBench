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
struct drm_gem_shmem_object {int madv; int /*<<< orphan*/  pages_lock; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

int drm_gem_shmem_madvise(struct drm_gem_object *obj, int madv)
{
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	mutex_lock(&shmem->pages_lock);

	if (shmem->madv >= 0)
		shmem->madv = madv;

	madv = shmem->madv;

	mutex_unlock(&shmem->pages_lock);

	return (madv >= 0);
}