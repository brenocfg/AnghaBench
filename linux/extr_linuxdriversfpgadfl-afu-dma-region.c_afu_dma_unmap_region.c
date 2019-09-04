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
typedef  int /*<<< orphan*/  u64 ;
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;
struct dfl_afu_dma_region {int /*<<< orphan*/  length; int /*<<< orphan*/  iova; scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EBUSY ; 
 int EINVAL ; 
 struct dfl_afu_dma_region* afu_dma_region_find_iova (struct dfl_feature_platform_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afu_dma_region_remove (struct dfl_feature_platform_data*,struct dfl_afu_dma_region*) ; 
 int /*<<< orphan*/  afu_dma_unpin_pages (struct dfl_feature_platform_data*,struct dfl_afu_dma_region*) ; 
 int /*<<< orphan*/  dfl_fpga_pdata_to_parent (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dfl_afu_dma_region*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int afu_dma_unmap_region(struct dfl_feature_platform_data *pdata, u64 iova)
{
	struct dfl_afu_dma_region *region;

	mutex_lock(&pdata->lock);
	region = afu_dma_region_find_iova(pdata, iova);
	if (!region) {
		mutex_unlock(&pdata->lock);
		return -EINVAL;
	}

	if (region->in_use) {
		mutex_unlock(&pdata->lock);
		return -EBUSY;
	}

	afu_dma_region_remove(pdata, region);
	mutex_unlock(&pdata->lock);

	dma_unmap_page(dfl_fpga_pdata_to_parent(pdata),
		       region->iova, region->length, DMA_BIDIRECTIONAL);
	afu_dma_unpin_pages(pdata, region);
	kfree(region);

	return 0;
}