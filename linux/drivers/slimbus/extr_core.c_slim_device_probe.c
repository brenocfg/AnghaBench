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
struct slim_driver {int (* probe ) (struct slim_device*) ;} ;
struct slim_device {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  SLIM_DEVICE_STATUS_UP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  slim_device_update_status (struct slim_device*,int /*<<< orphan*/ ) ; 
 int slim_get_logical_addr (struct slim_device*) ; 
 int stub1 (struct slim_device*) ; 
 struct slim_device* to_slim_device (struct device*) ; 
 struct slim_driver* to_slim_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slim_device_probe(struct device *dev)
{
	struct slim_device	*sbdev = to_slim_device(dev);
	struct slim_driver	*sbdrv = to_slim_driver(dev->driver);
	int ret;

	ret = sbdrv->probe(sbdev);
	if (ret)
		return ret;

	/* try getting the logical address after probe */
	ret = slim_get_logical_addr(sbdev);
	if (!ret) {
		slim_device_update_status(sbdev, SLIM_DEVICE_STATUS_UP);
	} else {
		dev_err(&sbdev->dev, "Failed to get logical address\n");
		ret = -EPROBE_DEFER;
	}

	return ret;
}