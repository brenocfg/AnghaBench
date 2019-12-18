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
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int firmware_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int translation_enabled(void)
{
#if defined(CONFIG_PPC_PASEMI_IOMMU_DMA_FORCE)
	return 1;
#else
	return firmware_has_feature(FW_FEATURE_LPAR);
#endif
}