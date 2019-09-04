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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ amd_iommu_last_bdf ; 

__attribute__((used)) static inline void update_last_devid(u16 devid)
{
	if (devid > amd_iommu_last_bdf)
		amd_iommu_last_bdf = devid;
}