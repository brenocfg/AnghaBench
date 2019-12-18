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
struct komeda_drv {int /*<<< orphan*/  mdev; int /*<<< orphan*/  kms; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct komeda_drv*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct komeda_drv*) ; 
 struct komeda_drv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_dev_create (struct device*) ; 
 int /*<<< orphan*/  komeda_dev_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_kms_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int komeda_bind(struct device *dev)
{
	struct komeda_drv *mdrv;
	int err;

	mdrv = devm_kzalloc(dev, sizeof(*mdrv), GFP_KERNEL);
	if (!mdrv)
		return -ENOMEM;

	mdrv->mdev = komeda_dev_create(dev);
	if (IS_ERR(mdrv->mdev)) {
		err = PTR_ERR(mdrv->mdev);
		goto free_mdrv;
	}

	mdrv->kms = komeda_kms_attach(mdrv->mdev);
	if (IS_ERR(mdrv->kms)) {
		err = PTR_ERR(mdrv->kms);
		goto destroy_mdev;
	}

	dev_set_drvdata(dev, mdrv);

	return 0;

destroy_mdev:
	komeda_dev_destroy(mdrv->mdev);

free_mdrv:
	devm_kfree(dev, mdrv);
	return err;
}