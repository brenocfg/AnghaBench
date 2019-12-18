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

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_DOMAIN_DMA ; 
 int /*<<< orphan*/  iommu_def_domain_type ; 
 int /*<<< orphan*/  iommu_set_cmd_line_dma_api () ; 

void iommu_set_default_translated(bool cmd_line)
{
	if (cmd_line)
		iommu_set_cmd_line_dma_api();

	iommu_def_domain_type = IOMMU_DOMAIN_DMA;
}