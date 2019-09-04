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
struct iommu_dev_data {struct protection_domain* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_detach (struct iommu_dev_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __detach_device(struct iommu_dev_data *dev_data)
{
	struct protection_domain *domain;

	domain = dev_data->domain;

	spin_lock(&domain->lock);

	do_detach(dev_data);

	spin_unlock(&domain->lock);
}