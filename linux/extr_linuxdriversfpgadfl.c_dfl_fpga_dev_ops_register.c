#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  devt; int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct module {int dummy; } ;
struct file_operations {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {TYPE_1__ kobj; struct module* owner; } ;
struct dfl_feature_platform_data {TYPE_3__ cdev; } ;

/* Variables and functions */
 int cdev_add (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_3__*,struct file_operations const*) ; 
 struct dfl_feature_platform_data* dev_get_platdata (TYPE_2__*) ; 

int dfl_fpga_dev_ops_register(struct platform_device *pdev,
			      const struct file_operations *fops,
			      struct module *owner)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&pdev->dev);

	cdev_init(&pdata->cdev, fops);
	pdata->cdev.owner = owner;

	/*
	 * set parent to the feature device so that its refcount is
	 * decreased after the last refcount of cdev is gone, that
	 * makes sure the feature device is valid during device
	 * file's life-cycle.
	 */
	pdata->cdev.kobj.parent = &pdev->dev.kobj;

	return cdev_add(&pdata->cdev, pdev->dev.devt, 1);
}