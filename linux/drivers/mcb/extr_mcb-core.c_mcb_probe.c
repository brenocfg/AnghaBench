#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct mcb_driver {int (* probe ) (struct mcb_device*,struct mcb_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct mcb_device_id {int dummy; } ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct mcb_device {TYPE_3__ dev; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {struct module* owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct mcb_device_id* mcb_match_id (int /*<<< orphan*/ ,struct mcb_device*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int stub1 (struct mcb_device*,struct mcb_device_id const*) ; 
 struct mcb_device* to_mcb_device (struct device*) ; 
 struct mcb_driver* to_mcb_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

__attribute__((used)) static int mcb_probe(struct device *dev)
{
	struct mcb_driver *mdrv = to_mcb_driver(dev->driver);
	struct mcb_device *mdev = to_mcb_device(dev);
	const struct mcb_device_id *found_id;
	struct module *carrier_mod;
	int ret;

	found_id = mcb_match_id(mdrv->id_table, mdev);
	if (!found_id)
		return -ENODEV;

	carrier_mod = mdev->dev.parent->driver->owner;
	if (!try_module_get(carrier_mod))
		return -EINVAL;

	get_device(dev);
	ret = mdrv->probe(mdev, found_id);
	if (ret)
		module_put(carrier_mod);

	return ret;
}