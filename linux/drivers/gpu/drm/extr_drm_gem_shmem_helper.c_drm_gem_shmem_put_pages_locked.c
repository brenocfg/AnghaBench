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
struct drm_gem_object {int dummy; } ;
struct drm_gem_shmem_object {scalar_t__ pages_use_count; int /*<<< orphan*/ * pages; int /*<<< orphan*/  pages_mark_accessed_on_put; int /*<<< orphan*/  pages_mark_dirty_on_put; struct drm_gem_object base; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_gem_shmem_put_pages_locked(struct drm_gem_shmem_object *shmem)
{
	struct drm_gem_object *obj = &shmem->base;

	if (WARN_ON_ONCE(!shmem->pages_use_count))
		return;

	if (--shmem->pages_use_count > 0)
		return;

	drm_gem_put_pages(obj, shmem->pages,
			  shmem->pages_mark_dirty_on_put,
			  shmem->pages_mark_accessed_on_put);
	shmem->pages = NULL;
}