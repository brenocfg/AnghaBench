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
struct protection_domain {int dummy; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int defer_attach; struct protection_domain* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct protection_domain* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_device (struct device*,struct protection_domain*) ; 
 int /*<<< orphan*/  check_device (struct device*) ; 
 int /*<<< orphan*/  dma_ops_domain (struct protection_domain*) ; 
 TYPE_1__* get_dev_data (struct device*) ; 
 struct iommu_domain* iommu_get_domain_for_dev (struct device*) ; 
 struct protection_domain* to_pdomain (struct iommu_domain*) ; 

__attribute__((used)) static struct protection_domain *get_domain(struct device *dev)
{
	struct protection_domain *domain;
	struct iommu_domain *io_domain;

	if (!check_device(dev))
		return ERR_PTR(-EINVAL);

	domain = get_dev_data(dev)->domain;
	if (domain == NULL && get_dev_data(dev)->defer_attach) {
		get_dev_data(dev)->defer_attach = false;
		io_domain = iommu_get_domain_for_dev(dev);
		domain = to_pdomain(io_domain);
		attach_device(dev, domain);
	}
	if (domain == NULL)
		return ERR_PTR(-EBUSY);

	if (!dma_ops_domain(domain))
		return ERR_PTR(-EBUSY);

	return domain;
}