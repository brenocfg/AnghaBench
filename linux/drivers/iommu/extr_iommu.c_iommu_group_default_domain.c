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
struct iommu_group {struct iommu_domain* default_domain; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */

struct iommu_domain *iommu_group_default_domain(struct iommu_group *group)
{
	return group->default_domain;
}