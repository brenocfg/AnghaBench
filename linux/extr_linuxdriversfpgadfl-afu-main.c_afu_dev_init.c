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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;
struct dfl_afu {struct dfl_feature_platform_data* pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  afu_dma_region_init (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  afu_mmio_region_init (struct dfl_feature_platform_data*) ; 
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct dfl_afu* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfl_fpga_pdata_set_private (struct dfl_feature_platform_data*,struct dfl_afu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afu_dev_init(struct platform_device *pdev)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct dfl_afu *afu;

	afu = devm_kzalloc(&pdev->dev, sizeof(*afu), GFP_KERNEL);
	if (!afu)
		return -ENOMEM;

	afu->pdata = pdata;

	mutex_lock(&pdata->lock);
	dfl_fpga_pdata_set_private(pdata, afu);
	afu_mmio_region_init(pdata);
	afu_dma_region_init(pdata);
	mutex_unlock(&pdata->lock);

	return 0;
}