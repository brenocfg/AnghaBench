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
struct udl_gem_object {int /*<<< orphan*/ * pages; struct sg_table* sg; } ;
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct udl_gem_object* udl_gem_alloc_object (struct drm_device*,int) ; 

__attribute__((used)) static int udl_prime_create(struct drm_device *dev,
			    size_t size,
			    struct sg_table *sg,
			    struct udl_gem_object **obj_p)
{
	struct udl_gem_object *obj;
	int npages;

	npages = size / PAGE_SIZE;

	*obj_p = NULL;
	obj = udl_gem_alloc_object(dev, npages * PAGE_SIZE);
	if (!obj)
		return -ENOMEM;

	obj->sg = sg;
	obj->pages = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (obj->pages == NULL) {
		DRM_ERROR("obj pages is NULL %d\n", npages);
		return -ENOMEM;
	}

	drm_prime_sg_to_page_addr_arrays(sg, obj->pages, NULL, npages);

	*obj_p = obj;
	return 0;
}