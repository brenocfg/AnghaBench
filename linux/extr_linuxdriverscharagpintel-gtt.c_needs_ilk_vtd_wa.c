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

/* Variables and functions */

__attribute__((used)) static inline int needs_ilk_vtd_wa(void)
{
#ifdef CONFIG_INTEL_IOMMU
	const unsigned short gpu_devid = intel_private.pcidev->device;

	/* Query intel_iommu to see if we need the workaround. Presumably that
	 * was loaded first.
	 */
	if ((gpu_devid == PCI_DEVICE_ID_INTEL_IRONLAKE_D_IG ||
	     gpu_devid == PCI_DEVICE_ID_INTEL_IRONLAKE_M_IG) &&
	     intel_iommu_gfx_mapped)
		return 1;
#endif
	return 0;
}