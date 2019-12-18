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
struct rio_driver {int (* probe ) (struct rio_dev*,struct rio_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct rio_device_id {int dummy; } ;
struct rio_dev {struct rio_driver* driver; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  rio_dev_get (struct rio_dev*) ; 
 int /*<<< orphan*/  rio_dev_put (struct rio_dev*) ; 
 struct rio_device_id* rio_match_device (int /*<<< orphan*/ ,struct rio_dev*) ; 
 int stub1 (struct rio_dev*,struct rio_device_id const*) ; 
 struct rio_dev* to_rio_dev (struct device*) ; 
 struct rio_driver* to_rio_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rio_device_probe(struct device *dev)
{
	struct rio_driver *rdrv = to_rio_driver(dev->driver);
	struct rio_dev *rdev = to_rio_dev(dev);
	int error = -ENODEV;
	const struct rio_device_id *id;

	if (!rdev->driver && rdrv->probe) {
		if (!rdrv->id_table)
			return error;
		id = rio_match_device(rdrv->id_table, rdev);
		rio_dev_get(rdev);
		if (id)
			error = rdrv->probe(rdev, id);
		if (error >= 0) {
			rdev->driver = rdrv;
			error = 0;
		} else
			rio_dev_put(rdev);
	}
	return error;
}