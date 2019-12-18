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
struct intel_th_driver {int /*<<< orphan*/  (* unassign ) (struct intel_th_device*,struct intel_th_device*) ;int /*<<< orphan*/  (* remove ) (struct intel_th_device*) ;scalar_t__ attr_group; } ;
struct TYPE_5__ {scalar_t__ driver; int /*<<< orphan*/  kobj; } ;
struct intel_th_device {scalar_t__ type; TYPE_2__ dev; } ;
struct intel_th {int num_thdevs; TYPE_3__** thdev; } ;
struct device {TYPE_1__* parent; int /*<<< orphan*/  driver; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 scalar_t__ INTEL_TH_OUTPUT ; 
 scalar_t__ INTEL_TH_SWITCH ; 
 int device_for_each_child (struct device*,struct intel_th_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_th_child_remove ; 
 int /*<<< orphan*/  intel_th_device_remove (TYPE_3__*) ; 
 scalar_t__ intel_th_output_assigned (struct intel_th_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct intel_th_device*) ; 
 int /*<<< orphan*/  stub2 (struct intel_th_device*,struct intel_th_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,scalar_t__) ; 
 struct intel_th* to_intel_th (struct intel_th_device*) ; 
 struct intel_th_device* to_intel_th_device (struct device*) ; 
 struct intel_th_driver* to_intel_th_driver (int /*<<< orphan*/ ) ; 
 struct intel_th_device* to_intel_th_hub (struct intel_th_device*) ; 

__attribute__((used)) static int intel_th_remove(struct device *dev)
{
	struct intel_th_driver *thdrv = to_intel_th_driver(dev->driver);
	struct intel_th_device *thdev = to_intel_th_device(dev);
	struct intel_th_device *hub = to_intel_th_hub(thdev);
	int err;

	if (thdev->type == INTEL_TH_SWITCH) {
		struct intel_th *th = to_intel_th(hub);
		int i, lowest;

		/* disconnect outputs */
		err = device_for_each_child(dev, thdev, intel_th_child_remove);
		if (err)
			return err;

		/*
		 * Remove outputs, that is, hub's children: they are created
		 * at hub's probe time by having the hub call
		 * intel_th_output_enable() for each of them.
		 */
		for (i = 0, lowest = -1; i < th->num_thdevs; i++) {
			/*
			 * Move the non-output devices from higher up the
			 * th->thdev[] array to lower positions to maintain
			 * a contiguous array.
			 */
			if (th->thdev[i]->type != INTEL_TH_OUTPUT) {
				if (lowest >= 0) {
					th->thdev[lowest] = th->thdev[i];
					th->thdev[i] = NULL;
					++lowest;
				}

				continue;
			}

			if (lowest == -1)
				lowest = i;

			intel_th_device_remove(th->thdev[i]);
			th->thdev[i] = NULL;
		}

		if (lowest >= 0)
			th->num_thdevs = lowest;
	}

	if (thdrv->attr_group)
		sysfs_remove_group(&thdev->dev.kobj, thdrv->attr_group);

	pm_runtime_get_sync(dev);

	thdrv->remove(thdev);

	if (intel_th_output_assigned(thdev)) {
		struct intel_th_driver *hubdrv =
			to_intel_th_driver(dev->parent->driver);

		if (hub->dev.driver)
			/* does not talk to hardware */
			hubdrv->unassign(hub, thdev);
	}

	pm_runtime_disable(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	return 0;
}