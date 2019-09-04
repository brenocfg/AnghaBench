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
struct omap_iommu {int dummy; } ;
struct cr_regs {int cam; int ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_CAM ; 
 int MMU_CAM_V ; 
 int /*<<< orphan*/  MMU_FLUSH_ENTRY ; 
 int /*<<< orphan*/  MMU_LD_TLB ; 
 int /*<<< orphan*/  MMU_RAM ; 
 int /*<<< orphan*/  iommu_write_reg (struct omap_iommu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iotlb_load_cr(struct omap_iommu *obj, struct cr_regs *cr)
{
	iommu_write_reg(obj, cr->cam | MMU_CAM_V, MMU_CAM);
	iommu_write_reg(obj, cr->ram, MMU_RAM);

	iommu_write_reg(obj, 1, MMU_FLUSH_ENTRY);
	iommu_write_reg(obj, 1, MMU_LD_TLB);
}