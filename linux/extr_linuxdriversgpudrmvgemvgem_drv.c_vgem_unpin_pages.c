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
struct drm_vgem_gem_object {scalar_t__ pages_pin_count; int /*<<< orphan*/  pages_lock; int /*<<< orphan*/ * pages; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_put_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vgem_unpin_pages(struct drm_vgem_gem_object *bo)
{
	mutex_lock(&bo->pages_lock);
	if (--bo->pages_pin_count == 0) {
		drm_gem_put_pages(&bo->base, bo->pages, true, true);
		bo->pages = NULL;
	}
	mutex_unlock(&bo->pages_lock);
}