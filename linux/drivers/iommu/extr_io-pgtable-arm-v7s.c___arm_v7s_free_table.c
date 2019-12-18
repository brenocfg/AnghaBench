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

/* Variables and functions */
 size_t ARM_V7S_TABLE_SIZE (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  __arm_v7s_dma_addr (void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void __arm_v7s_free_table(void *table, int lvl,
				 struct arm_v7s_io_pgtable *data)
{
	struct io_pgtable_cfg *cfg = &data->iop.cfg;
	struct device *dev = cfg->iommu_dev;
	size_t size = ARM_V7S_TABLE_SIZE(lvl);

	if (!cfg->coherent_walk)
		dma_unmap_single(dev, __arm_v7s_dma_addr(table), size,
				 DMA_TO_DEVICE);
	if (lvl == 1)
		free_pages((unsigned long)table, get_order(size));
	else
		kmem_cache_free(data->l2_tables, table);
}