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
 struct komeda_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct komeda_drv*) ; 
 int /*<<< orphan*/  komeda_dev_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_kms_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void komeda_unbind(struct device *dev)
{
	struct komeda_drv *mdrv = dev_get_drvdata(dev);

	if (!mdrv)
		return;

	komeda_kms_detach(mdrv->kms);
	komeda_dev_destroy(mdrv->mdev);

	dev_set_drvdata(dev, NULL);
	devm_kfree(dev, mdrv);
}