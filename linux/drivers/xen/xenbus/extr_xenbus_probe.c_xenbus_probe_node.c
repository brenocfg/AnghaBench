#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; } ;
struct xenbus_device {int state; char* nodename; char* devicetype; TYPE_1__ dev; int /*<<< orphan*/  down; } ;
struct xen_bus_type {int (* get_bus_id ) (char*,char*) ;int /*<<< orphan*/  bus; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XEN_BUS_ID_SIZE ; 
 int XenbusStateInitialising ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,char*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xenbus_device*) ; 
 struct xenbus_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int stub1 (char*,char*) ; 
 int /*<<< orphan*/  xenbus_dev_release ; 
 int xenbus_read_driver_state (char const*) ; 

int xenbus_probe_node(struct xen_bus_type *bus,
		      const char *type,
		      const char *nodename)
{
	char devname[XEN_BUS_ID_SIZE];
	int err;
	struct xenbus_device *xendev;
	size_t stringlen;
	char *tmpstring;

	enum xenbus_state state = xenbus_read_driver_state(nodename);

	if (state != XenbusStateInitialising) {
		/* Device is not new, so ignore it.  This can happen if a
		   device is going away after switching to Closed.  */
		return 0;
	}

	stringlen = strlen(nodename) + 1 + strlen(type) + 1;
	xendev = kzalloc(sizeof(*xendev) + stringlen, GFP_KERNEL);
	if (!xendev)
		return -ENOMEM;

	xendev->state = XenbusStateInitialising;

	/* Copy the strings into the extra space. */

	tmpstring = (char *)(xendev + 1);
	strcpy(tmpstring, nodename);
	xendev->nodename = tmpstring;

	tmpstring += strlen(tmpstring) + 1;
	strcpy(tmpstring, type);
	xendev->devicetype = tmpstring;
	init_completion(&xendev->down);

	xendev->dev.bus = &bus->bus;
	xendev->dev.release = xenbus_dev_release;

	err = bus->get_bus_id(devname, xendev->nodename);
	if (err)
		goto fail;

	dev_set_name(&xendev->dev, "%s", devname);

	/* Register with generic device framework. */
	err = device_register(&xendev->dev);
	if (err) {
		put_device(&xendev->dev);
		xendev = NULL;
		goto fail;
	}

	return 0;
fail:
	kfree(xendev);
	return err;
}