#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  devt; } ;
struct scom_device {int dead; TYPE_1__ dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct scom_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fsi_free_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int scom_remove(struct device *dev)
{
	struct scom_device *scom = dev_get_drvdata(dev);

	mutex_lock(&scom->lock);
	scom->dead = true;
	mutex_unlock(&scom->lock);
	cdev_device_del(&scom->cdev, &scom->dev);
	fsi_free_minor(scom->dev.devt);
	put_device(&scom->dev);

	return 0;
}