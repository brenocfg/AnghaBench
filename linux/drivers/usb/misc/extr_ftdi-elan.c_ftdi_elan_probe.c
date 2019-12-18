#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  minor; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {int bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct usb_ftdi {int expected; int bulk_in_endpointAddr; int bulk_out_endpointAddr; TYPE_2__* udev; int /*<<< orphan*/  respond_work; int /*<<< orphan*/  command_work; int /*<<< orphan*/  status_work; int /*<<< orphan*/ * class; int /*<<< orphan*/  bulk_in_buffer; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  u132_lock; struct usb_interface* interface; int /*<<< orphan*/  sw_lock; scalar_t__ sequence_num; int /*<<< orphan*/  ftdi_list; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ftdi_elan_command_work ; 
 int /*<<< orphan*/  ftdi_elan_init_kref (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_elan_jtag_class ; 
 int /*<<< orphan*/  ftdi_elan_put_kref (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_elan_respond_work ; 
 int /*<<< orphan*/  ftdi_elan_status_work ; 
 scalar_t__ ftdi_instances ; 
 int /*<<< orphan*/  ftdi_module_lock ; 
 int /*<<< orphan*/  ftdi_static_list ; 
 int /*<<< orphan*/  ftdi_status_queue_work (struct usb_ftdi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_ftdi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int usb_find_common_endpoints (struct usb_host_interface*,struct usb_endpoint_descriptor**,struct usb_endpoint_descriptor**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* usb_get_dev (int /*<<< orphan*/ ) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_ftdi*) ; 

__attribute__((used)) static int ftdi_elan_probe(struct usb_interface *interface,
			   const struct usb_device_id *id)
{
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *bulk_in, *bulk_out;
	int retval;
	struct usb_ftdi *ftdi;

	ftdi = kzalloc(sizeof(struct usb_ftdi), GFP_KERNEL);
	if (!ftdi)
		return -ENOMEM;

	mutex_lock(&ftdi_module_lock);
	list_add_tail(&ftdi->ftdi_list, &ftdi_static_list);
	ftdi->sequence_num = ++ftdi_instances;
	mutex_unlock(&ftdi_module_lock);
	ftdi_elan_init_kref(ftdi);
	sema_init(&ftdi->sw_lock, 1);
	ftdi->udev = usb_get_dev(interface_to_usbdev(interface));
	ftdi->interface = interface;
	mutex_init(&ftdi->u132_lock);
	ftdi->expected = 4;

	iface_desc = interface->cur_altsetting;
	retval = usb_find_common_endpoints(iface_desc,
			&bulk_in, &bulk_out, NULL, NULL);
	if (retval) {
		dev_err(&ftdi->udev->dev, "Could not find both bulk-in and bulk-out endpoints\n");
		goto error;
	}

	ftdi->bulk_in_size = usb_endpoint_maxp(bulk_in);
	ftdi->bulk_in_endpointAddr = bulk_in->bEndpointAddress;
	ftdi->bulk_in_buffer = kmalloc(ftdi->bulk_in_size, GFP_KERNEL);
	if (!ftdi->bulk_in_buffer) {
		retval = -ENOMEM;
		goto error;
	}

	ftdi->bulk_out_endpointAddr = bulk_out->bEndpointAddress;

	dev_info(&ftdi->udev->dev, "interface %d has I=%02X O=%02X\n",
		 iface_desc->desc.bInterfaceNumber, ftdi->bulk_in_endpointAddr,
		 ftdi->bulk_out_endpointAddr);
	usb_set_intfdata(interface, ftdi);
	if (iface_desc->desc.bInterfaceNumber == 0 &&
	    ftdi->bulk_in_endpointAddr == 0x81 &&
	    ftdi->bulk_out_endpointAddr == 0x02) {
		retval = usb_register_dev(interface, &ftdi_elan_jtag_class);
		if (retval) {
			dev_err(&ftdi->udev->dev, "Not able to get a minor for this device\n");
			usb_set_intfdata(interface, NULL);
			retval = -ENOMEM;
			goto error;
		} else {
			ftdi->class = &ftdi_elan_jtag_class;
			dev_info(&ftdi->udev->dev, "USB FDTI=%p JTAG interface %d now attached to ftdi%d\n",
				 ftdi, iface_desc->desc.bInterfaceNumber,
				 interface->minor);
			return 0;
		}
	} else if (iface_desc->desc.bInterfaceNumber == 1 &&
		   ftdi->bulk_in_endpointAddr == 0x83 &&
		   ftdi->bulk_out_endpointAddr == 0x04) {
		ftdi->class = NULL;
		dev_info(&ftdi->udev->dev, "USB FDTI=%p ELAN interface %d now activated\n",
			 ftdi, iface_desc->desc.bInterfaceNumber);
		INIT_DELAYED_WORK(&ftdi->status_work, ftdi_elan_status_work);
		INIT_DELAYED_WORK(&ftdi->command_work, ftdi_elan_command_work);
		INIT_DELAYED_WORK(&ftdi->respond_work, ftdi_elan_respond_work);
		ftdi_status_queue_work(ftdi, msecs_to_jiffies(3 *1000));
		return 0;
	} else {
		dev_err(&ftdi->udev->dev,
			"Could not find ELAN's U132 device\n");
		retval = -ENODEV;
		goto error;
	}
error:if (ftdi) {
		ftdi_elan_put_kref(ftdi);
	}
	return retval;
}