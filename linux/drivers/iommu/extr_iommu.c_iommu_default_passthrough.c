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
 scalar_t__ IOMMU_DOMAIN_IDENTITY ; 
 scalar_t__ iommu_def_domain_type ; 

bool iommu_default_passthrough(void)
{
	return iommu_def_domain_type == IOMMU_DOMAIN_IDENTITY;
}