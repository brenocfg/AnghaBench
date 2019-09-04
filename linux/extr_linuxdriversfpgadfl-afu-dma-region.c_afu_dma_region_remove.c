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
struct dfl_feature_platform_data {TYPE_1__* dev; } ;
struct dfl_afu_dma_region {int /*<<< orphan*/  node; scalar_t__ iova; } ;
struct dfl_afu {int /*<<< orphan*/  dma_regions; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 struct dfl_afu* dfl_fpga_pdata_get_private (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afu_dma_region_remove(struct dfl_feature_platform_data *pdata,
				  struct dfl_afu_dma_region *region)
{
	struct dfl_afu *afu;

	dev_dbg(&pdata->dev->dev, "del region (iova = %llx)\n",
		(unsigned long long)region->iova);

	afu = dfl_fpga_pdata_get_private(pdata);
	rb_erase(&region->node, &afu->dma_regions);
}