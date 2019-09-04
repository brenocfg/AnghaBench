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
struct iommu_ops {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool arm_setup_iommu_dma_ops(struct device *dev, u64 dma_base, u64 size,
				    const struct iommu_ops *iommu)
{
	return false;
}