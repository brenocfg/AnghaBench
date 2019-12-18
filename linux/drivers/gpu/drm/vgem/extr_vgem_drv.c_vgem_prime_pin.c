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
struct drm_vgem_gem_object {int dummy; } ;
struct drm_gem_object {long size; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 long PAGE_SHIFT ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  drm_clflush_pages (struct page**,long) ; 
 struct drm_vgem_gem_object* to_vgem_bo (struct drm_gem_object*) ; 
 struct page** vgem_pin_pages (struct drm_vgem_gem_object*) ; 

__attribute__((used)) static int vgem_prime_pin(struct drm_gem_object *obj)
{
	struct drm_vgem_gem_object *bo = to_vgem_bo(obj);
	long n_pages = obj->size >> PAGE_SHIFT;
	struct page **pages;

	pages = vgem_pin_pages(bo);
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	/* Flush the object from the CPU cache so that importers can rely
	 * on coherent indirect access via the exported dma-address.
	 */
	drm_clflush_pages(pages, n_pages);

	return 0;
}