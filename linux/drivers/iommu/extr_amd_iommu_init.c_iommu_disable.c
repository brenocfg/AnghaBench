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
struct amd_iommu {int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_CMDBUF_EN ; 
 int /*<<< orphan*/  CONTROL_EVT_INT_EN ; 
 int /*<<< orphan*/  CONTROL_EVT_LOG_EN ; 
 int /*<<< orphan*/  CONTROL_GAINT_EN ; 
 int /*<<< orphan*/  CONTROL_GALOG_EN ; 
 int /*<<< orphan*/  CONTROL_IOMMU_EN ; 
 int /*<<< orphan*/  iommu_feature_disable (struct amd_iommu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_disable(struct amd_iommu *iommu)
{
	if (!iommu->mmio_base)
		return;

	/* Disable command buffer */
	iommu_feature_disable(iommu, CONTROL_CMDBUF_EN);

	/* Disable event logging and event interrupts */
	iommu_feature_disable(iommu, CONTROL_EVT_INT_EN);
	iommu_feature_disable(iommu, CONTROL_EVT_LOG_EN);

	/* Disable IOMMU GA_LOG */
	iommu_feature_disable(iommu, CONTROL_GALOG_EN);
	iommu_feature_disable(iommu, CONTROL_GAINT_EN);

	/* Disable IOMMU hardware itself */
	iommu_feature_disable(iommu, CONTROL_IOMMU_EN);
}