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
struct omap_iommu {scalar_t__ has_bus_err_back; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; scalar_t__ iopgd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_GP_REG ; 
 int MMU_GP_REG_BUS_ERR_BACK_EN ; 
 int /*<<< orphan*/  MMU_REVISION ; 
 int /*<<< orphan*/  MMU_TTB ; 
 int /*<<< orphan*/  SZ_16K ; 
 int /*<<< orphan*/  __iommu_set_twl (struct omap_iommu*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dra7_cfg_dspsys_mmu (struct omap_iommu*,int) ; 
 int iommu_read_reg (struct omap_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_write_reg (struct omap_iommu*,int,int /*<<< orphan*/ ) ; 
 int virt_to_phys (scalar_t__) ; 

__attribute__((used)) static int omap2_iommu_enable(struct omap_iommu *obj)
{
	u32 l, pa;

	if (!obj->iopgd || !IS_ALIGNED((u32)obj->iopgd,  SZ_16K))
		return -EINVAL;

	pa = virt_to_phys(obj->iopgd);
	if (!IS_ALIGNED(pa, SZ_16K))
		return -EINVAL;

	l = iommu_read_reg(obj, MMU_REVISION);
	dev_info(obj->dev, "%s: version %d.%d\n", obj->name,
		 (l >> 4) & 0xf, l & 0xf);

	iommu_write_reg(obj, pa, MMU_TTB);

	dra7_cfg_dspsys_mmu(obj, true);

	if (obj->has_bus_err_back)
		iommu_write_reg(obj, MMU_GP_REG_BUS_ERR_BACK_EN, MMU_GP_REG);

	__iommu_set_twl(obj, true);

	return 0;
}