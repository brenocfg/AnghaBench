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
 int /*<<< orphan*/  IOMMU_CMD_LINE_DMA_API ; 
 int /*<<< orphan*/  iommu_cmd_line ; 

__attribute__((used)) static void iommu_set_cmd_line_dma_api(void)
{
	iommu_cmd_line |= IOMMU_CMD_LINE_DMA_API;
}