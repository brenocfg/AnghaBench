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
typedef  int /*<<< orphan*/  u32 ;
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;
struct dfl_afu_mmio_region {int dummy; } ;
struct dfl_afu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct dfl_afu* dfl_fpga_pdata_get_private (struct dfl_feature_platform_data*) ; 
 struct dfl_afu_mmio_region* get_region_by_index (struct dfl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int afu_mmio_region_get_by_index(struct dfl_feature_platform_data *pdata,
				 u32 region_index,
				 struct dfl_afu_mmio_region *pregion)
{
	struct dfl_afu_mmio_region *region;
	struct dfl_afu *afu;
	int ret = 0;

	mutex_lock(&pdata->lock);
	afu = dfl_fpga_pdata_get_private(pdata);
	region = get_region_by_index(afu, region_index);
	if (!region) {
		ret = -EINVAL;
		goto exit;
	}
	*pregion = *region;
exit:
	mutex_unlock(&pdata->lock);
	return ret;
}