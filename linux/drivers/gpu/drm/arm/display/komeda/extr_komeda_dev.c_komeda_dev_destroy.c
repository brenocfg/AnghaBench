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
struct komeda_dev_funcs {int /*<<< orphan*/  (* cleanup ) (struct komeda_dev*) ;int /*<<< orphan*/  (* disconnect_iommu ) (struct komeda_dev*) ;} ;
struct komeda_dev {int n_pipelines; int /*<<< orphan*/ * aclk; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/ ** pipelines; int /*<<< orphan*/ * iommu; struct komeda_dev_funcs* funcs; int /*<<< orphan*/  debugfs_root; struct device* dev; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_put (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_iounmap (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct komeda_dev*) ; 
 int /*<<< orphan*/  komeda_pipeline_destroy (struct komeda_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  komeda_sysfs_attr_group ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct komeda_dev*) ; 
 int /*<<< orphan*/  stub2 (struct komeda_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void komeda_dev_destroy(struct komeda_dev *mdev)
{
	struct device *dev = mdev->dev;
	const struct komeda_dev_funcs *funcs = mdev->funcs;
	int i;

	sysfs_remove_group(&dev->kobj, &komeda_sysfs_attr_group);

#ifdef CONFIG_DEBUG_FS
	debugfs_remove_recursive(mdev->debugfs_root);
#endif

	if (mdev->iommu && mdev->funcs->disconnect_iommu)
		mdev->funcs->disconnect_iommu(mdev);
	mdev->iommu = NULL;

	for (i = 0; i < mdev->n_pipelines; i++) {
		komeda_pipeline_destroy(mdev, mdev->pipelines[i]);
		mdev->pipelines[i] = NULL;
	}

	mdev->n_pipelines = 0;

	of_reserved_mem_device_release(dev);

	if (funcs && funcs->cleanup)
		funcs->cleanup(mdev);

	if (mdev->reg_base) {
		devm_iounmap(dev, mdev->reg_base);
		mdev->reg_base = NULL;
	}

	if (mdev->aclk) {
		clk_disable_unprepare(mdev->aclk);
		devm_clk_put(dev, mdev->aclk);
		mdev->aclk = NULL;
	}

	devm_kfree(dev, mdev);
}