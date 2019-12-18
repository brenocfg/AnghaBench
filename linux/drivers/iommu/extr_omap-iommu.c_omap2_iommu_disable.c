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
struct omap_iommu {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_CNTL ; 
 int /*<<< orphan*/  MMU_CNTL_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dra7_cfg_dspsys_mmu (struct omap_iommu*,int) ; 
 int /*<<< orphan*/  iommu_read_reg (struct omap_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_write_reg (struct omap_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_iommu_disable(struct omap_iommu *obj)
{
	u32 l = iommu_read_reg(obj, MMU_CNTL);

	l &= ~MMU_CNTL_MASK;
	iommu_write_reg(obj, l, MMU_CNTL);
	dra7_cfg_dspsys_mmu(obj, false);

	dev_dbg(obj->dev, "%s is shutting down\n", obj->name);
}