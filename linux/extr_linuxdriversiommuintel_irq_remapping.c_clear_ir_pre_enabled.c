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
struct intel_iommu {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTD_FLAG_IRQ_REMAP_PRE_ENABLED ; 

__attribute__((used)) static void clear_ir_pre_enabled(struct intel_iommu *iommu)
{
	iommu->flags &= ~VTD_FLAG_IRQ_REMAP_PRE_ENABLED;
}