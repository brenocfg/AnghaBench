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
struct etnaviv_iommu_domain {int dummy; } ;

/* Variables and functions */
 size_t PT_SIZE ; 

__attribute__((used)) static size_t etnaviv_iommuv1_dump_size(struct etnaviv_iommu_domain *domain)
{
	return PT_SIZE;
}