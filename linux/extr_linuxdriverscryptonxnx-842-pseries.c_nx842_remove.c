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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct vio_dev {TYPE_1__ dev; } ;
struct nx842_devdata {struct nx842_devdata* counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devdata ; 
 int /*<<< orphan*/  devdata_mutex ; 
 int /*<<< orphan*/  kfree (struct nx842_devdata*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nx842_attribute_group ; 
 int /*<<< orphan*/  nx842_of_nb ; 
 int /*<<< orphan*/  nx842_pseries_alg ; 
 int /*<<< orphan*/  of_reconfig_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct nx842_devdata* rcu_dereference_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nx842_remove(struct vio_dev *viodev)
{
	struct nx842_devdata *old_devdata;
	unsigned long flags;

	pr_info("Removing IBM Power 842 compression device\n");
	sysfs_remove_group(&viodev->dev.kobj, &nx842_attribute_group);

	crypto_unregister_alg(&nx842_pseries_alg);

	spin_lock_irqsave(&devdata_mutex, flags);
	old_devdata = rcu_dereference_check(devdata,
			lockdep_is_held(&devdata_mutex));
	of_reconfig_notifier_unregister(&nx842_of_nb);
	RCU_INIT_POINTER(devdata, NULL);
	spin_unlock_irqrestore(&devdata_mutex, flags);
	synchronize_rcu();
	dev_set_drvdata(&viodev->dev, NULL);
	if (old_devdata)
		kfree(old_devdata->counters);
	kfree(old_devdata);

	return 0;
}