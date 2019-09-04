#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int /*<<< orphan*/ * name; struct device* dev; int /*<<< orphan*/  ref; int /*<<< orphan*/  prio; int /*<<< orphan*/  lock; int /*<<< orphan*/  subdevs; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct v4l2_device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_init (int /*<<< orphan*/ *) ; 

int v4l2_device_register(struct device *dev, struct v4l2_device *v4l2_dev)
{
	if (v4l2_dev == NULL)
		return -EINVAL;

	INIT_LIST_HEAD(&v4l2_dev->subdevs);
	spin_lock_init(&v4l2_dev->lock);
	v4l2_prio_init(&v4l2_dev->prio);
	kref_init(&v4l2_dev->ref);
	get_device(dev);
	v4l2_dev->dev = dev;
	if (dev == NULL) {
		/* If dev == NULL, then name must be filled in by the caller */
		if (WARN_ON(!v4l2_dev->name[0]))
			return -EINVAL;
		return 0;
	}

	/* Set name to driver name + device name if it is empty. */
	if (!v4l2_dev->name[0])
		snprintf(v4l2_dev->name, sizeof(v4l2_dev->name), "%s %s",
			dev->driver->name, dev_name(dev));
	if (!dev_get_drvdata(dev))
		dev_set_drvdata(dev, v4l2_dev);
	return 0;
}