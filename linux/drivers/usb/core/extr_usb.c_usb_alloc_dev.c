#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {TYPE_1__* driver; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; struct TYPE_14__* parent; int /*<<< orphan*/  dma_pfn_offset; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct TYPE_12__ {int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct TYPE_13__ {TYPE_2__ desc; int /*<<< orphan*/  urb_list; } ;
struct usb_device {int lpm_disable_count; int can_submit; char* devpath; int level; unsigned int portnum; int wusb; int /*<<< orphan*/  authorized; void* active_duration; void* connect_time; TYPE_4__ dev; int /*<<< orphan*/  filelist; struct usb_device* parent; struct usb_bus* bus; scalar_t__ route; TYPE_3__ ep0; int /*<<< orphan*/  urbnum; int /*<<< orphan*/  state; } ;
struct usb_bus {int /*<<< orphan*/  busnum; TYPE_7__* sysdev; TYPE_4__* controller; } ;
struct TYPE_15__ {int /*<<< orphan*/  dma_pfn_offset; int /*<<< orphan*/  dma_mask; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* alloc_dev ) (struct usb_hcd*,struct usb_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_DT_ENDPOINT ; 
 int /*<<< orphan*/  USB_DT_ENDPOINT_SIZE ; 
 int /*<<< orphan*/  USB_STATE_ATTACHED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_hcd* bus_to_hcd (struct usb_bus*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_4__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_to_node (TYPE_7__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_4__*) ; 
 int /*<<< orphan*/  device_set_of_node_from_dev (TYPE_4__*,TYPE_7__*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kfree (struct usb_device*) ; 
 struct usb_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_4__*,int) ; 
 int /*<<< orphan*/  set_dev_node (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct usb_device*) ; 
 scalar_t__ unlikely (int) ; 
 int usb_autosuspend_delay ; 
 scalar_t__ usb_bus_is_wusb (struct usb_bus*) ; 
 int /*<<< orphan*/  usb_bus_type ; 
 int /*<<< orphan*/  usb_dev_authorized (struct usb_device*,struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_device_groups ; 
 int /*<<< orphan*/  usb_device_type ; 
 int /*<<< orphan*/  usb_enable_endpoint (struct usb_device*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  usb_get_hcd (struct usb_hcd*) ; 
 unsigned int usb_hcd_find_raw_port_number (struct usb_hcd*,unsigned int) ; 
 int /*<<< orphan*/  usb_of_get_device_node (struct usb_device*,unsigned int) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

struct usb_device *usb_alloc_dev(struct usb_device *parent,
				 struct usb_bus *bus, unsigned port1)
{
	struct usb_device *dev;
	struct usb_hcd *usb_hcd = bus_to_hcd(bus);
	unsigned root_hub = 0;
	unsigned raw_port = port1;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	if (!usb_get_hcd(usb_hcd)) {
		kfree(dev);
		return NULL;
	}
	/* Root hubs aren't true devices, so don't allocate HCD resources */
	if (usb_hcd->driver->alloc_dev && parent &&
		!usb_hcd->driver->alloc_dev(usb_hcd, dev)) {
		usb_put_hcd(bus_to_hcd(bus));
		kfree(dev);
		return NULL;
	}

	device_initialize(&dev->dev);
	dev->dev.bus = &usb_bus_type;
	dev->dev.type = &usb_device_type;
	dev->dev.groups = usb_device_groups;
	/*
	 * Fake a dma_mask/offset for the USB device:
	 * We cannot really use the dma-mapping API (dma_alloc_* and
	 * dma_map_*) for USB devices but instead need to use
	 * usb_alloc_coherent and pass data in 'urb's, but some subsystems
	 * manually look into the mask/offset pair to determine whether
	 * they need bounce buffers.
	 * Note: calling dma_set_mask() on a USB device would set the
	 * mask for the entire HCD, so don't do that.
	 */
	dev->dev.dma_mask = bus->sysdev->dma_mask;
	dev->dev.dma_pfn_offset = bus->sysdev->dma_pfn_offset;
	set_dev_node(&dev->dev, dev_to_node(bus->sysdev));
	dev->state = USB_STATE_ATTACHED;
	dev->lpm_disable_count = 1;
	atomic_set(&dev->urbnum, 0);

	INIT_LIST_HEAD(&dev->ep0.urb_list);
	dev->ep0.desc.bLength = USB_DT_ENDPOINT_SIZE;
	dev->ep0.desc.bDescriptorType = USB_DT_ENDPOINT;
	/* ep0 maxpacket comes later, from device descriptor */
	usb_enable_endpoint(dev, &dev->ep0, false);
	dev->can_submit = 1;

	/* Save readable and stable topology id, distinguishing devices
	 * by location for diagnostics, tools, driver model, etc.  The
	 * string is a path along hub ports, from the root.  Each device's
	 * dev->devpath will be stable until USB is re-cabled, and hubs
	 * are often labeled with these port numbers.  The name isn't
	 * as stable:  bus->busnum changes easily from modprobe order,
	 * cardbus or pci hotplugging, and so on.
	 */
	if (unlikely(!parent)) {
		dev->devpath[0] = '0';
		dev->route = 0;

		dev->dev.parent = bus->controller;
		device_set_of_node_from_dev(&dev->dev, bus->sysdev);
		dev_set_name(&dev->dev, "usb%d", bus->busnum);
		root_hub = 1;
	} else {
		/* match any labeling on the hubs; it's one-based */
		if (parent->devpath[0] == '0') {
			snprintf(dev->devpath, sizeof dev->devpath,
				"%d", port1);
			/* Root ports are not counted in route string */
			dev->route = 0;
		} else {
			snprintf(dev->devpath, sizeof dev->devpath,
				"%s.%d", parent->devpath, port1);
			/* Route string assumes hubs have less than 16 ports */
			if (port1 < 15)
				dev->route = parent->route +
					(port1 << ((parent->level - 1)*4));
			else
				dev->route = parent->route +
					(15 << ((parent->level - 1)*4));
		}

		dev->dev.parent = &parent->dev;
		dev_set_name(&dev->dev, "%d-%s", bus->busnum, dev->devpath);

		if (!parent->parent) {
			/* device under root hub's port */
			raw_port = usb_hcd_find_raw_port_number(usb_hcd,
				port1);
		}
		dev->dev.of_node = usb_of_get_device_node(parent, raw_port);

		/* hub driver sets up TT records */
	}

	dev->portnum = port1;
	dev->bus = bus;
	dev->parent = parent;
	INIT_LIST_HEAD(&dev->filelist);

#ifdef	CONFIG_PM
	pm_runtime_set_autosuspend_delay(&dev->dev,
			usb_autosuspend_delay * 1000);
	dev->connect_time = jiffies;
	dev->active_duration = -jiffies;
#endif

	dev->authorized = usb_dev_authorized(dev, usb_hcd);
	if (!root_hub)
		dev->wusb = usb_bus_is_wusb(bus) ? 1 : 0;

	return dev;
}