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
typedef  int u32 ;
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INV_IOMMU_ALL_PAGES_ADDRESS ; 
 int /*<<< orphan*/  build_inv_iommu_pages (struct iommu_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 

__attribute__((used)) static void amd_iommu_flush_tlb_all(struct amd_iommu *iommu)
{
	u32 dom_id;

	for (dom_id = 0; dom_id <= 0xffff; ++dom_id) {
		struct iommu_cmd cmd;
		build_inv_iommu_pages(&cmd, 0, CMD_INV_IOMMU_ALL_PAGES_ADDRESS,
				      dom_id, 1);
		iommu_queue_command(iommu, &cmd);
	}

	iommu_completion_wait(iommu);
}