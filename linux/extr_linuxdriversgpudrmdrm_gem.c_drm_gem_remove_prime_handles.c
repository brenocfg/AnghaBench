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
struct drm_gem_object {scalar_t__ dma_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_file {TYPE_1__ prime; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_prime_remove_buf_handle_locked (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
drm_gem_remove_prime_handles(struct drm_gem_object *obj, struct drm_file *filp)
{
	/*
	 * Note: obj->dma_buf can't disappear as long as we still hold a
	 * handle reference in obj->handle_count.
	 */
	mutex_lock(&filp->prime.lock);
	if (obj->dma_buf) {
		drm_prime_remove_buf_handle_locked(&filp->prime,
						   obj->dma_buf);
	}
	mutex_unlock(&filp->prime.lock);
}