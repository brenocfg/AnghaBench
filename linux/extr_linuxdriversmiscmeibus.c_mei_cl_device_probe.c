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
struct mei_cl_driver {int (* probe ) (struct mei_cl_device*,struct mei_cl_device_id const*) ;} ;
struct mei_cl_device_id {int dummy; } ;
struct mei_cl_device {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mei_cl_bus_module_get (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_cl_bus_module_put (struct mei_cl_device*) ; 
 struct mei_cl_device_id* mei_cl_device_find (struct mei_cl_device*,struct mei_cl_driver*) ; 
 int stub1 (struct mei_cl_device*,struct mei_cl_device_id const*) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 
 struct mei_cl_driver* to_mei_cl_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_cl_device_probe(struct device *dev)
{
	struct mei_cl_device *cldev;
	struct mei_cl_driver *cldrv;
	const struct mei_cl_device_id *id;
	int ret;

	cldev = to_mei_cl_device(dev);
	cldrv = to_mei_cl_driver(dev->driver);

	if (!cldev)
		return 0;

	if (!cldrv || !cldrv->probe)
		return -ENODEV;

	id = mei_cl_device_find(cldev, cldrv);
	if (!id)
		return -ENODEV;

	if (!mei_cl_bus_module_get(cldev)) {
		dev_err(&cldev->dev, "get hw module failed");
		return -ENODEV;
	}

	ret = cldrv->probe(cldev, id);
	if (ret) {
		mei_cl_bus_module_put(cldev);
		return ret;
	}

	__module_get(THIS_MODULE);
	return 0;
}