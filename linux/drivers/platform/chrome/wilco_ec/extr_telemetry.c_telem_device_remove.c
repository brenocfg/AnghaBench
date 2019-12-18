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
struct telem_device_data {TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct telem_device_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  telem_ida ; 

__attribute__((used)) static int telem_device_remove(struct platform_device *pdev)
{
	struct telem_device_data *dev_data = platform_get_drvdata(pdev);

	cdev_device_del(&dev_data->cdev, &dev_data->dev);
	put_device(&dev_data->dev);
	ida_simple_remove(&telem_ida, MINOR(dev_data->dev.devt));

	return 0;
}