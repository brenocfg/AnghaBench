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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct xenbus_device {TYPE_1__ dev; int /*<<< orphan*/  nodename; } ;
struct backend_info {struct backend_info* hotplug_script; int /*<<< orphan*/ * vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_OFFLINE ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 struct backend_info* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct backend_info*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_backend_state (struct backend_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_hotplug_status_watch (struct backend_info*) ; 
 int /*<<< orphan*/  xen_unregister_watchers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_rm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xenvif_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netback_remove(struct xenbus_device *dev)
{
	struct backend_info *be = dev_get_drvdata(&dev->dev);

	set_backend_state(be, XenbusStateClosed);

	unregister_hotplug_status_watch(be);
	if (be->vif) {
		kobject_uevent(&dev->dev.kobj, KOBJ_OFFLINE);
		xen_unregister_watchers(be->vif);
		xenbus_rm(XBT_NIL, dev->nodename, "hotplug-status");
		xenvif_free(be->vif);
		be->vif = NULL;
	}
	kfree(be->hotplug_script);
	kfree(be);
	dev_set_drvdata(&dev->dev, NULL);
	return 0;
}