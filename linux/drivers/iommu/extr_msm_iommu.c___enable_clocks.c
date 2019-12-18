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
struct msm_iommu_dev {scalar_t__ pclk; scalar_t__ clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int clk_enable (scalar_t__) ; 

__attribute__((used)) static int __enable_clocks(struct msm_iommu_dev *iommu)
{
	int ret;

	ret = clk_enable(iommu->pclk);
	if (ret)
		goto fail;

	if (iommu->clk) {
		ret = clk_enable(iommu->clk);
		if (ret)
			clk_disable(iommu->pclk);
	}
fail:
	return ret;
}