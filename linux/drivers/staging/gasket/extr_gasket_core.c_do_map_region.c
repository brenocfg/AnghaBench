#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct vm_area_struct {int vm_end; int vm_start; int vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct gasket_mappable_region {int start; int length_bytes; } ;
struct gasket_driver_desc {scalar_t__ legacy_mmap_address_offset; } ;
struct gasket_dev {int /*<<< orphan*/  dev; TYPE_2__* bar_data; TYPE_1__* internal_desc; } ;
typedef  enum do_map_region_status { ____Placeholder_do_map_region_status } do_map_region_status ;
struct TYPE_4__ {int phys_base; } ;
struct TYPE_3__ {struct gasket_driver_desc* driver_desc; } ;

/* Variables and functions */
 int DO_MAP_REGION_FAILURE ; 
 int DO_MAP_REGION_INVALID ; 
 int DO_MAP_REGION_SUCCESS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int gasket_get_bar_index (struct gasket_dev const*,scalar_t__) ; 
 int /*<<< orphan*/  gasket_mm_get_mapping_addrs (struct gasket_mappable_region*,int,int,struct gasket_mappable_region*,int*) ; 
 scalar_t__ gasket_mm_unmap_region (struct gasket_dev const*,struct vm_area_struct*,struct gasket_mappable_region*) ; 
 int gasket_mm_vma_bar_offset (struct gasket_dev const*,struct vm_area_struct*,int*) ; 
 int io_remap_pfn_range (struct vm_area_struct*,int,int,int,int /*<<< orphan*/ ) ; 
 int min (int const,int) ; 

__attribute__((used)) static enum do_map_region_status
do_map_region(const struct gasket_dev *gasket_dev, struct vm_area_struct *vma,
	      struct gasket_mappable_region *mappable_region)
{
	/* Maximum size of a single call to io_remap_pfn_range. */
	/* I pulled this number out of thin air. */
	const ulong max_chunk_size = 64 * 1024 * 1024;
	ulong chunk_size, mapped_bytes = 0;

	const struct gasket_driver_desc *driver_desc =
		gasket_dev->internal_desc->driver_desc;

	ulong bar_offset, virt_offset;
	struct gasket_mappable_region region_to_map;
	ulong phys_offset, map_length;
	ulong virt_base, phys_base;
	int bar_index, ret;

	ret = gasket_mm_vma_bar_offset(gasket_dev, vma, &bar_offset);
	if (ret)
		return DO_MAP_REGION_INVALID;

	if (!gasket_mm_get_mapping_addrs(mappable_region, bar_offset,
					 vma->vm_end - vma->vm_start,
					 &region_to_map, &virt_offset))
		return DO_MAP_REGION_INVALID;
	phys_offset = region_to_map.start;
	map_length = region_to_map.length_bytes;

	virt_base = vma->vm_start + virt_offset;
	bar_index =
		gasket_get_bar_index(gasket_dev,
				     (vma->vm_pgoff << PAGE_SHIFT) +
				     driver_desc->legacy_mmap_address_offset);
	phys_base = gasket_dev->bar_data[bar_index].phys_base + phys_offset;
	while (mapped_bytes < map_length) {
		/*
		 * io_remap_pfn_range can take a while, so we chunk its
		 * calls and call cond_resched between each.
		 */
		chunk_size = min(max_chunk_size, map_length - mapped_bytes);

		cond_resched();
		ret = io_remap_pfn_range(vma, virt_base + mapped_bytes,
					 (phys_base + mapped_bytes) >>
					 PAGE_SHIFT, chunk_size,
					 vma->vm_page_prot);
		if (ret) {
			dev_err(gasket_dev->dev,
				"Error remapping PFN range.\n");
			goto fail;
		}
		mapped_bytes += chunk_size;
	}

	return DO_MAP_REGION_SUCCESS;

fail:
	/* Unmap the partial chunk we mapped. */
	mappable_region->length_bytes = mapped_bytes;
	if (gasket_mm_unmap_region(gasket_dev, vma, mappable_region))
		dev_err(gasket_dev->dev,
			"Error unmapping partial region 0x%lx (0x%lx bytes)\n",
			(ulong)virt_offset,
			(ulong)mapped_bytes);

	return DO_MAP_REGION_FAILURE;
}