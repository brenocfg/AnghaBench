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
struct resource {int dummy; } ;
struct deferred_device {int /*<<< orphan*/  node; struct resource* parent; struct amba_device* dev; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFERRED_DEVICE_TIMEOUT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amba_device_try_add (struct amba_device*,struct resource*) ; 
 int /*<<< orphan*/  deferred_devices ; 
 int /*<<< orphan*/  deferred_devices_lock ; 
 int /*<<< orphan*/  deferred_retry_work ; 
 struct deferred_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int amba_device_add(struct amba_device *dev, struct resource *parent)
{
	int ret = amba_device_try_add(dev, parent);

	if (ret == -EPROBE_DEFER) {
		struct deferred_device *ddev;

		ddev = kmalloc(sizeof(*ddev), GFP_KERNEL);
		if (!ddev)
			return -ENOMEM;

		ddev->dev = dev;
		ddev->parent = parent;
		ret = 0;

		mutex_lock(&deferred_devices_lock);

		if (list_empty(&deferred_devices))
			schedule_delayed_work(&deferred_retry_work,
					      DEFERRED_DEVICE_TIMEOUT);
		list_add_tail(&ddev->node, &deferred_devices);

		mutex_unlock(&deferred_devices_lock);
	}
	return ret;
}