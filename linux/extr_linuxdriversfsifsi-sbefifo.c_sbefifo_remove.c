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
struct sbefifo {int dead; TYPE_1__ dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct sbefifo* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_free_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  sbefifo_unregister_child ; 

__attribute__((used)) static int sbefifo_remove(struct device *dev)
{
	struct sbefifo *sbefifo = dev_get_drvdata(dev);

	dev_dbg(dev, "Removing sbefifo device...\n");

	mutex_lock(&sbefifo->lock);
	sbefifo->dead = true;
	mutex_unlock(&sbefifo->lock);

	cdev_device_del(&sbefifo->cdev, &sbefifo->dev);
	fsi_free_minor(sbefifo->dev.devt);
	device_for_each_child(dev, NULL, sbefifo_unregister_child);
	put_device(&sbefifo->dev);

	return 0;
}