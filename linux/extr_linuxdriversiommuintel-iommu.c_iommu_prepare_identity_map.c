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
struct dmar_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DOMAIN_ADDRESS_WIDTH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  domain_exit (struct dmar_domain*) ; 
 int domain_prepare_identity_map (struct device*,struct dmar_domain*,unsigned long long,unsigned long long) ; 
 struct dmar_domain* get_domain_for_dev (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iommu_prepare_identity_map(struct device *dev,
				      unsigned long long start,
				      unsigned long long end)
{
	struct dmar_domain *domain;
	int ret;

	domain = get_domain_for_dev(dev, DEFAULT_DOMAIN_ADDRESS_WIDTH);
	if (!domain)
		return -ENOMEM;

	ret = domain_prepare_identity_map(dev, domain, start, end);
	if (ret)
		domain_exit(domain);

	return ret;
}