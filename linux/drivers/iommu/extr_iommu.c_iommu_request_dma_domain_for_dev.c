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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_DOMAIN_DMA ; 
 int request_default_domain_for_dev (struct device*,int /*<<< orphan*/ ) ; 

int iommu_request_dma_domain_for_dev(struct device *dev)
{
	return request_default_domain_for_dev(dev, IOMMU_DOMAIN_DMA);
}