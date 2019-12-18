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

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_shmem_put_pages_locked (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_gem_shmem_put_pages(struct drm_gem_shmem_object *shmem)
{
	mutex_lock(&shmem->pages_lock);
	drm_gem_shmem_put_pages_locked(shmem);
	mutex_unlock(&shmem->pages_lock);
}