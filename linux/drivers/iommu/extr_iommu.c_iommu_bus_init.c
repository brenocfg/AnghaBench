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
struct notifier_block {int /*<<< orphan*/  notifier_call; } ;
struct iommu_ops {int dummy; } ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_iommu_group ; 
 int bus_for_each_dev (struct bus_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_register_notifier (struct bus_type*,struct notifier_block*) ; 
 int /*<<< orphan*/  bus_unregister_notifier (struct bus_type*,struct notifier_block*) ; 
 int /*<<< orphan*/  iommu_bus_notifier ; 
 int /*<<< orphan*/  kfree (struct notifier_block*) ; 
 struct notifier_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_iommu_group ; 

__attribute__((used)) static int iommu_bus_init(struct bus_type *bus, const struct iommu_ops *ops)
{
	int err;
	struct notifier_block *nb;

	nb = kzalloc(sizeof(struct notifier_block), GFP_KERNEL);
	if (!nb)
		return -ENOMEM;

	nb->notifier_call = iommu_bus_notifier;

	err = bus_register_notifier(bus, nb);
	if (err)
		goto out_free;

	err = bus_for_each_dev(bus, NULL, NULL, add_iommu_group);
	if (err)
		goto out_err;


	return 0;

out_err:
	/* Clean up */
	bus_for_each_dev(bus, NULL, NULL, remove_iommu_group);
	bus_unregister_notifier(bus, nb);

out_free:
	kfree(nb);

	return err;
}