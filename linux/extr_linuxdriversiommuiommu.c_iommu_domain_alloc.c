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
struct iommu_domain {int dummy; } ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_DOMAIN_UNMANAGED ; 
 struct iommu_domain* __iommu_domain_alloc (struct bus_type*,int /*<<< orphan*/ ) ; 

struct iommu_domain *iommu_domain_alloc(struct bus_type *bus)
{
	return __iommu_domain_alloc(bus, IOMMU_DOMAIN_UNMANAGED);
}