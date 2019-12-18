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
struct kvmgt_guest_info {struct intel_vgpu* vgpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  cache_lock; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;
struct gvt_dma {unsigned long size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int __gvt_cache_add (struct intel_vgpu*,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 struct gvt_dma* __gvt_cache_find_gfn (struct intel_vgpu*,unsigned long) ; 
 int /*<<< orphan*/  __gvt_cache_remove_entry (struct intel_vgpu*,struct gvt_dma*) ; 
 int gvt_dma_map_page (struct intel_vgpu*,unsigned long,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  gvt_dma_unmap_page (struct intel_vgpu*,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_valid (unsigned long) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvmgt_dma_map_guest_page(unsigned long handle, unsigned long gfn,
		unsigned long size, dma_addr_t *dma_addr)
{
	struct kvmgt_guest_info *info;
	struct intel_vgpu *vgpu;
	struct gvt_dma *entry;
	int ret;

	if (!handle_valid(handle))
		return -EINVAL;

	info = (struct kvmgt_guest_info *)handle;
	vgpu = info->vgpu;

	mutex_lock(&info->vgpu->vdev.cache_lock);

	entry = __gvt_cache_find_gfn(info->vgpu, gfn);
	if (!entry) {
		ret = gvt_dma_map_page(vgpu, gfn, dma_addr, size);
		if (ret)
			goto err_unlock;

		ret = __gvt_cache_add(info->vgpu, gfn, *dma_addr, size);
		if (ret)
			goto err_unmap;
	} else if (entry->size != size) {
		/* the same gfn with different size: unmap and re-map */
		gvt_dma_unmap_page(vgpu, gfn, entry->dma_addr, entry->size);
		__gvt_cache_remove_entry(vgpu, entry);

		ret = gvt_dma_map_page(vgpu, gfn, dma_addr, size);
		if (ret)
			goto err_unlock;

		ret = __gvt_cache_add(info->vgpu, gfn, *dma_addr, size);
		if (ret)
			goto err_unmap;
	} else {
		kref_get(&entry->ref);
		*dma_addr = entry->dma_addr;
	}

	mutex_unlock(&info->vgpu->vdev.cache_lock);
	return 0;

err_unmap:
	gvt_dma_unmap_page(vgpu, gfn, *dma_addr, size);
err_unlock:
	mutex_unlock(&info->vgpu->vdev.cache_lock);
	return ret;
}