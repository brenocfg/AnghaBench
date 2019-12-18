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
struct kobject {int dummy; } ;
struct iommu_group {struct iommu_group* name; scalar_t__ default_domain; int /*<<< orphan*/  id; int /*<<< orphan*/  iommu_data; int /*<<< orphan*/  (* iommu_data_release ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_domain_free (scalar_t__) ; 
 int /*<<< orphan*/  iommu_group_ida ; 
 int /*<<< orphan*/  kfree (struct iommu_group*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct iommu_group* to_iommu_group (struct kobject*) ; 

__attribute__((used)) static void iommu_group_release(struct kobject *kobj)
{
	struct iommu_group *group = to_iommu_group(kobj);

	pr_debug("Releasing group %d\n", group->id);

	if (group->iommu_data_release)
		group->iommu_data_release(group->iommu_data);

	ida_simple_remove(&iommu_group_ida, group->id);

	if (group->default_domain)
		iommu_domain_free(group->default_domain);

	kfree(group->name);
	kfree(group);
}