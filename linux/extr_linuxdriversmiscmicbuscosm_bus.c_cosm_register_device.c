#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cosm_hw_ops {int dummy; } ;
struct TYPE_5__ {int id; int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; struct device* parent; } ;
struct cosm_device {int index; TYPE_1__ dev; struct cosm_hw_ops* hw_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cosm_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cosm_bus ; 
 int /*<<< orphan*/  cosm_index_ida ; 
 int /*<<< orphan*/  cosm_release_dev ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct cosm_device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_register (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 struct cosm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

struct cosm_device *
cosm_register_device(struct device *pdev, struct cosm_hw_ops *hw_ops)
{
	struct cosm_device *cdev;
	int ret;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return ERR_PTR(-ENOMEM);

	cdev->dev.parent = pdev;
	cdev->dev.release = cosm_release_dev;
	cdev->hw_ops = hw_ops;
	dev_set_drvdata(&cdev->dev, cdev);
	cdev->dev.bus = &cosm_bus;

	/* Assign a unique device index and hence name */
	ret = ida_simple_get(&cosm_index_ida, 0, 0, GFP_KERNEL);
	if (ret < 0)
		goto free_cdev;

	cdev->index = ret;
	cdev->dev.id = ret;
	dev_set_name(&cdev->dev, "cosm-dev%u", cdev->index);

	ret = device_register(&cdev->dev);
	if (ret)
		goto ida_remove;
	return cdev;
ida_remove:
	ida_simple_remove(&cosm_index_ida, cdev->index);
free_cdev:
	put_device(&cdev->dev);
	return ERR_PTR(ret);
}