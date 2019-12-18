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
struct cr_regs {void* ram; void* cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_READ_CAM ; 
 int /*<<< orphan*/  MMU_READ_RAM ; 
 void* iommu_read_reg (struct omap_iommu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iotlb_read_cr(struct omap_iommu *obj, struct cr_regs *cr)
{
	cr->cam = iommu_read_reg(obj, MMU_READ_CAM);
	cr->ram = iommu_read_reg(obj, MMU_READ_RAM);
}