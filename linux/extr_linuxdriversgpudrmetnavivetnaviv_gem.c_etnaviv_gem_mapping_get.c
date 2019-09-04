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
struct page {int dummy; } ;
struct etnaviv_vram_mapping {int use; int /*<<< orphan*/  obj_node; TYPE_1__* mmu; struct etnaviv_gem_object* object; int /*<<< orphan*/  scan_node; } ;
struct etnaviv_gpu {int /*<<< orphan*/  memory_base; TYPE_1__* mmu; } ;
struct etnaviv_gem_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  vram_list; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct etnaviv_vram_mapping* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 struct page** etnaviv_gem_get_pages (struct etnaviv_gem_object*) ; 
 struct etnaviv_vram_mapping* etnaviv_gem_get_vram_mapping (struct etnaviv_gem_object*,TYPE_1__*) ; 
 int etnaviv_iommu_map_gem (TYPE_1__*,struct etnaviv_gem_object*,int /*<<< orphan*/ ,struct etnaviv_vram_mapping*) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_vram_mapping*) ; 
 struct etnaviv_vram_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 

struct etnaviv_vram_mapping *etnaviv_gem_mapping_get(
	struct drm_gem_object *obj, struct etnaviv_gpu *gpu)
{
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	struct etnaviv_vram_mapping *mapping;
	struct page **pages;
	int ret = 0;

	mutex_lock(&etnaviv_obj->lock);
	mapping = etnaviv_gem_get_vram_mapping(etnaviv_obj, gpu->mmu);
	if (mapping) {
		/*
		 * Holding the object lock prevents the use count changing
		 * beneath us.  If the use count is zero, the MMU might be
		 * reaping this object, so take the lock and re-check that
		 * the MMU owns this mapping to close this race.
		 */
		if (mapping->use == 0) {
			mutex_lock(&gpu->mmu->lock);
			if (mapping->mmu == gpu->mmu)
				mapping->use += 1;
			else
				mapping = NULL;
			mutex_unlock(&gpu->mmu->lock);
			if (mapping)
				goto out;
		} else {
			mapping->use += 1;
			goto out;
		}
	}

	pages = etnaviv_gem_get_pages(etnaviv_obj);
	if (IS_ERR(pages)) {
		ret = PTR_ERR(pages);
		goto out;
	}

	/*
	 * See if we have a reaped vram mapping we can re-use before
	 * allocating a fresh mapping.
	 */
	mapping = etnaviv_gem_get_vram_mapping(etnaviv_obj, NULL);
	if (!mapping) {
		mapping = kzalloc(sizeof(*mapping), GFP_KERNEL);
		if (!mapping) {
			ret = -ENOMEM;
			goto out;
		}

		INIT_LIST_HEAD(&mapping->scan_node);
		mapping->object = etnaviv_obj;
	} else {
		list_del(&mapping->obj_node);
	}

	mapping->mmu = gpu->mmu;
	mapping->use = 1;

	ret = etnaviv_iommu_map_gem(gpu->mmu, etnaviv_obj, gpu->memory_base,
				    mapping);
	if (ret < 0)
		kfree(mapping);
	else
		list_add_tail(&mapping->obj_node, &etnaviv_obj->vram_list);

out:
	mutex_unlock(&etnaviv_obj->lock);

	if (ret)
		return ERR_PTR(ret);

	/* Take a reference on the object */
	drm_gem_object_get(obj);
	return mapping;
}