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
struct io_pgtable_cfg {int /*<<< orphan*/  coherent_walk; struct device* iommu_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct io_pgtable_cfg cfg; } ;
struct arm_v7s_io_pgtable {int /*<<< orphan*/  l2_tables; TYPE_1__ iop; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;
typedef  scalar_t__ arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_TABLE_GFP_DMA ; 
 size_t ARM_V7S_TABLE_SIZE (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ dma_map_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 void* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_ignore (void*) ; 
 scalar_t__ virt_to_phys (void*) ; 

__attribute__((used)) static void *__arm_v7s_alloc_table(int lvl, gfp_t gfp,
				   struct arm_v7s_io_pgtable *data)
{
	struct io_pgtable_cfg *cfg = &data->iop.cfg;
	struct device *dev = cfg->iommu_dev;
	phys_addr_t phys;
	dma_addr_t dma;
	size_t size = ARM_V7S_TABLE_SIZE(lvl);
	void *table = NULL;

	if (lvl == 1)
		table = (void *)__get_free_pages(
			__GFP_ZERO | ARM_V7S_TABLE_GFP_DMA, get_order(size));
	else if (lvl == 2)
		table = kmem_cache_zalloc(data->l2_tables, gfp);
	phys = virt_to_phys(table);
	if (phys != (arm_v7s_iopte)phys) {
		/* Doesn't fit in PTE */
		dev_err(dev, "Page table does not fit in PTE: %pa", &phys);
		goto out_free;
	}
	if (table && !cfg->coherent_walk) {
		dma = dma_map_single(dev, table, size, DMA_TO_DEVICE);
		if (dma_mapping_error(dev, dma))
			goto out_free;
		/*
		 * We depend on the IOMMU being able to work with any physical
		 * address directly, so if the DMA layer suggests otherwise by
		 * translating or truncating them, that bodes very badly...
		 */
		if (dma != phys)
			goto out_unmap;
	}
	if (lvl == 2)
		kmemleak_ignore(table);
	return table;

out_unmap:
	dev_err(dev, "Cannot accommodate DMA translation for IOMMU page tables\n");
	dma_unmap_single(dev, dma, size, DMA_TO_DEVICE);
out_free:
	if (lvl == 1)
		free_pages((unsigned long)table, get_order(size));
	else
		kmem_cache_free(data->l2_tables, table);
	return NULL;
}