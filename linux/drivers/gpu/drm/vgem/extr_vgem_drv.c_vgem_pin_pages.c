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
struct page {int dummy; } ;
struct drm_vgem_gem_object {struct page** pages; int /*<<< orphan*/  pages_lock; int /*<<< orphan*/  pages_pin_count; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 struct page** drm_gem_get_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page **vgem_pin_pages(struct drm_vgem_gem_object *bo)
{
	mutex_lock(&bo->pages_lock);
	if (bo->pages_pin_count++ == 0) {
		struct page **pages;

		pages = drm_gem_get_pages(&bo->base);
		if (IS_ERR(pages)) {
			bo->pages_pin_count--;
			mutex_unlock(&bo->pages_lock);
			return pages;
		}

		bo->pages = pages;
	}
	mutex_unlock(&bo->pages_lock);

	return bo->pages;
}