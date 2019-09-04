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
struct dfl_feature_platform_data {int dummy; } ;
struct dfl_afu {int /*<<< orphan*/  dma_regions; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 
 struct dfl_afu* dfl_fpga_pdata_get_private (struct dfl_feature_platform_data*) ; 

void afu_dma_region_init(struct dfl_feature_platform_data *pdata)
{
	struct dfl_afu *afu = dfl_fpga_pdata_get_private(pdata);

	afu->dma_regions = RB_ROOT;
}