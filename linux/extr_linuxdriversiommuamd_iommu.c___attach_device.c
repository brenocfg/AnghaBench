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
struct protection_domain {int /*<<< orphan*/  lock; } ;
struct iommu_dev_data {int /*<<< orphan*/ * domain; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  do_attach (struct iommu_dev_data*,struct protection_domain*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __attach_device(struct iommu_dev_data *dev_data,
			   struct protection_domain *domain)
{
	int ret;

	/* lock domain */
	spin_lock(&domain->lock);

	ret = -EBUSY;
	if (dev_data->domain != NULL)
		goto out_unlock;

	/* Attach alias group root */
	do_attach(dev_data, domain);

	ret = 0;

out_unlock:

	/* ready */
	spin_unlock(&domain->lock);

	return ret;
}