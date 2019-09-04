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
typedef  unsigned long long u8 ;
typedef  unsigned long long u64 ;
struct amd_iommu {scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ MMIO_CONTROL_OFFSET ; 
 unsigned long long readq (scalar_t__) ; 
 int /*<<< orphan*/  writeq (unsigned long long,scalar_t__) ; 

__attribute__((used)) static void iommu_feature_disable(struct amd_iommu *iommu, u8 bit)
{
	u64 ctrl;

	ctrl = readq(iommu->mmio_base + MMIO_CONTROL_OFFSET);
	ctrl &= ~(1ULL << bit);
	writeq(ctrl, iommu->mmio_base + MMIO_CONTROL_OFFSET);
}