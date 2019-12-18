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
struct xen_gem_object {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 struct xen_gem_object* to_xen_gem_obj (struct drm_gem_object*) ; 
 void* vmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *xen_drm_front_gem_prime_vmap(struct drm_gem_object *gem_obj)
{
	struct xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);

	if (!xen_obj->pages)
		return NULL;

	/* Please see comment in gem_mmap_obj on mapping and attributes. */
	return vmap(xen_obj->pages, xen_obj->num_pages,
		    VM_MAP, PAGE_KERNEL);
}