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
struct xen_gem_object {struct page** pages; } ;
struct page {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct xen_gem_object* to_xen_gem_obj (struct drm_gem_object*) ; 

struct page **xen_drm_front_gem_get_pages(struct drm_gem_object *gem_obj)
{
	struct xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);

	return xen_obj->pages;
}