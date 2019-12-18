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
struct greybus_driver {int (* probe ) (struct gb_bundle*,struct greybus_bundle_id const*) ;int /*<<< orphan*/  id_table; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_bundle {TYPE_1__* intf; int /*<<< orphan*/  id; int /*<<< orphan*/  connections; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {struct device dev; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GB_BUNDLE_AUTOSUSPEND_MS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int gb_control_bundle_activate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_control_bundle_deactivate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct greybus_bundle_id* greybus_match_id (struct gb_bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int stub1 (struct gb_bundle*,struct greybus_bundle_id const*) ; 
 struct gb_bundle* to_gb_bundle (struct device*) ; 
 struct greybus_driver* to_greybus_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int greybus_probe(struct device *dev)
{
	struct greybus_driver *driver = to_greybus_driver(dev->driver);
	struct gb_bundle *bundle = to_gb_bundle(dev);
	const struct greybus_bundle_id *id;
	int retval;

	/* match id */
	id = greybus_match_id(bundle, driver->id_table);
	if (!id)
		return -ENODEV;

	retval = pm_runtime_get_sync(&bundle->intf->dev);
	if (retval < 0) {
		pm_runtime_put_noidle(&bundle->intf->dev);
		return retval;
	}

	retval = gb_control_bundle_activate(bundle->intf->control, bundle->id);
	if (retval) {
		pm_runtime_put(&bundle->intf->dev);
		return retval;
	}

	/*
	 * Unbound bundle devices are always deactivated. During probe, the
	 * Runtime PM is set to enabled and active and the usage count is
	 * incremented. If the driver supports runtime PM, it should call
	 * pm_runtime_put() in its probe routine and pm_runtime_get_sync()
	 * in remove routine.
	 */
	pm_runtime_set_autosuspend_delay(dev, GB_BUNDLE_AUTOSUSPEND_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	retval = driver->probe(bundle, id);
	if (retval) {
		/*
		 * Catch buggy drivers that fail to destroy their connections.
		 */
		WARN_ON(!list_empty(&bundle->connections));

		gb_control_bundle_deactivate(bundle->intf->control, bundle->id);

		pm_runtime_disable(dev);
		pm_runtime_set_suspended(dev);
		pm_runtime_put_noidle(dev);
		pm_runtime_dont_use_autosuspend(dev);
		pm_runtime_put(&bundle->intf->dev);

		return retval;
	}

	pm_runtime_put(&bundle->intf->dev);

	return 0;
}