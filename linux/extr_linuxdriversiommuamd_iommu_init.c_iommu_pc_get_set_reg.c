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
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct amd_iommu {int max_banks; int max_counters; scalar_t__ mmio_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MMIO_CNTR_REG_OFFSET ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  amd_iommu_pc_present ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int iommu_pc_get_set_reg(struct amd_iommu *iommu, u8 bank, u8 cntr,
				u8 fxn, u64 *value, bool is_write)
{
	u32 offset;
	u32 max_offset_lim;

	/* Make sure the IOMMU PC resource is available */
	if (!amd_iommu_pc_present)
		return -ENODEV;

	/* Check for valid iommu and pc register indexing */
	if (WARN_ON(!iommu || (fxn > 0x28) || (fxn & 7)))
		return -ENODEV;

	offset = (u32)(((0x40 | bank) << 12) | (cntr << 8) | fxn);

	/* Limit the offset to the hw defined mmio region aperture */
	max_offset_lim = (u32)(((0x40 | iommu->max_banks) << 12) |
				(iommu->max_counters << 8) | 0x28);
	if ((offset < MMIO_CNTR_REG_OFFSET) ||
	    (offset > max_offset_lim))
		return -EINVAL;

	if (is_write) {
		u64 val = *value & GENMASK_ULL(47, 0);

		writel((u32)val, iommu->mmio_base + offset);
		writel((val >> 32), iommu->mmio_base + offset + 4);
	} else {
		*value = readl(iommu->mmio_base + offset + 4);
		*value <<= 32;
		*value |= readl(iommu->mmio_base + offset);
		*value &= GENMASK_ULL(47, 0);
	}

	return 0;
}