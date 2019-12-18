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
struct komeda_drv {struct komeda_dev* mdev; } ;
struct komeda_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct komeda_drv* dev_get_drvdata (struct device*) ; 

struct komeda_dev *dev_to_mdev(struct device *dev)
{
	struct komeda_drv *mdrv = dev_get_drvdata(dev);

	return mdrv ? mdrv->mdev : NULL;
}