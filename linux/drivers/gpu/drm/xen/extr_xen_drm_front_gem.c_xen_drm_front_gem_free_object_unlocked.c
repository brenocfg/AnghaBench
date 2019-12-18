#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ import_attach; } ;
struct xen_gem_object {scalar_t__ pages; TYPE_1__ base; int /*<<< orphan*/  num_pages; scalar_t__ be_alloc; int /*<<< orphan*/  sgt_imported; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_put_pages (TYPE_1__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xenballooned_pages (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gem_free_pages_array (struct xen_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct xen_gem_object*) ; 
 struct xen_gem_object* to_xen_gem_obj (struct drm_gem_object*) ; 

void xen_drm_front_gem_free_object_unlocked(struct drm_gem_object *gem_obj)
{
	struct xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);

	if (xen_obj->base.import_attach) {
		drm_prime_gem_destroy(&xen_obj->base, xen_obj->sgt_imported);
		gem_free_pages_array(xen_obj);
	} else {
		if (xen_obj->pages) {
			if (xen_obj->be_alloc) {
				free_xenballooned_pages(xen_obj->num_pages,
							xen_obj->pages);
				gem_free_pages_array(xen_obj);
			} else {
				drm_gem_put_pages(&xen_obj->base,
						  xen_obj->pages, true, false);
			}
		}
	}
	drm_gem_object_release(gem_obj);
	kfree(xen_obj);
}