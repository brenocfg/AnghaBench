#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dmar_domain {int dummy; } ;
struct device_domain_info {struct dmar_domain* domain; } ;
struct TYPE_2__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 scalar_t__ likely (struct device_domain_info*) ; 

__attribute__((used)) static struct dmar_domain *find_domain(struct device *dev)
{
	struct device_domain_info *info;

	/* No lock here, assumes no domain exit in normal case */
	info = dev->archdata.iommu;
	if (likely(info))
		return info->domain;
	return NULL;
}