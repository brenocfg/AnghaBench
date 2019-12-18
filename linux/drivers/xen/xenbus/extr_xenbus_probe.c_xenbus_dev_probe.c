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
struct xenbus_driver {int (* probe ) (struct xenbus_device*,struct xenbus_device_id const*) ;int /*<<< orphan*/  ids; } ;
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct xenbus_device_id* match_device (int /*<<< orphan*/ ,struct xenbus_device*) ; 
 int stub1 (struct xenbus_device*,struct xenbus_device_id const*) ; 
 int talk_to_otherend (struct xenbus_device*) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 
 struct xenbus_driver* to_xenbus_driver (int /*<<< orphan*/ ) ; 
 int watch_otherend (struct xenbus_device*) ; 
 int /*<<< orphan*/  xenbus_dev_error (struct xenbus_device*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

int xenbus_dev_probe(struct device *_dev)
{
	struct xenbus_device *dev = to_xenbus_device(_dev);
	struct xenbus_driver *drv = to_xenbus_driver(_dev->driver);
	const struct xenbus_device_id *id;
	int err;

	DPRINTK("%s", dev->nodename);

	if (!drv->probe) {
		err = -ENODEV;
		goto fail;
	}

	id = match_device(drv->ids, dev);
	if (!id) {
		err = -ENODEV;
		goto fail;
	}

	err = talk_to_otherend(dev);
	if (err) {
		dev_warn(&dev->dev, "talk_to_otherend on %s failed.\n",
			 dev->nodename);
		return err;
	}

	err = drv->probe(dev, id);
	if (err)
		goto fail;

	err = watch_otherend(dev);
	if (err) {
		dev_warn(&dev->dev, "watch_otherend on %s failed.\n",
		       dev->nodename);
		return err;
	}

	return 0;
fail:
	xenbus_dev_error(dev, err, "xenbus_dev_probe on %s", dev->nodename);
	xenbus_switch_state(dev, XenbusStateClosed);
	return err;
}