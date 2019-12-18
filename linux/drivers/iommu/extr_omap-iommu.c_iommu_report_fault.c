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
struct omap_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_FAULT_AD ; 
 int /*<<< orphan*/  MMU_IRQSTATUS ; 
 int /*<<< orphan*/  MMU_IRQ_MASK ; 
 int /*<<< orphan*/  iommu_read_reg (struct omap_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_write_reg (struct omap_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iommu_report_fault(struct omap_iommu *obj, u32 *da)
{
	u32 status, fault_addr;

	status = iommu_read_reg(obj, MMU_IRQSTATUS);
	status &= MMU_IRQ_MASK;
	if (!status) {
		*da = 0;
		return 0;
	}

	fault_addr = iommu_read_reg(obj, MMU_FAULT_AD);
	*da = fault_addr;

	iommu_write_reg(obj, status, MMU_IRQSTATUS);

	return status;
}