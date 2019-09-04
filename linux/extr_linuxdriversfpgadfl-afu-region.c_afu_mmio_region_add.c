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
typedef  void* u64 ;
typedef  void* u32 ;
struct dfl_feature_platform_data {TYPE_1__* dev; int /*<<< orphan*/  lock; } ;
struct dfl_afu_mmio_region {int /*<<< orphan*/  node; int /*<<< orphan*/  offset; void* flags; void* phys; void* size; void* index; } ;
struct dfl_afu {int /*<<< orphan*/  num_regions; int /*<<< orphan*/  region_cur_offset; int /*<<< orphan*/  regions; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PAGE_ALIGN (void*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct dfl_afu_mmio_region*) ; 
 struct dfl_afu_mmio_region* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct dfl_afu* dfl_fpga_pdata_get_private (struct dfl_feature_platform_data*) ; 
 scalar_t__ get_region_by_index (struct dfl_afu*,void*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int afu_mmio_region_add(struct dfl_feature_platform_data *pdata,
			u32 region_index, u64 region_size, u64 phys, u32 flags)
{
	struct dfl_afu_mmio_region *region;
	struct dfl_afu *afu;
	int ret = 0;

	region = devm_kzalloc(&pdata->dev->dev, sizeof(*region), GFP_KERNEL);
	if (!region)
		return -ENOMEM;

	region->index = region_index;
	region->size = region_size;
	region->phys = phys;
	region->flags = flags;

	mutex_lock(&pdata->lock);

	afu = dfl_fpga_pdata_get_private(pdata);

	/* check if @index already exists */
	if (get_region_by_index(afu, region_index)) {
		mutex_unlock(&pdata->lock);
		ret = -EEXIST;
		goto exit;
	}

	region_size = PAGE_ALIGN(region_size);
	region->offset = afu->region_cur_offset;
	list_add(&region->node, &afu->regions);

	afu->region_cur_offset += region_size;
	afu->num_regions++;
	mutex_unlock(&pdata->lock);

	return 0;

exit:
	devm_kfree(&pdata->dev->dev, region);
	return ret;
}