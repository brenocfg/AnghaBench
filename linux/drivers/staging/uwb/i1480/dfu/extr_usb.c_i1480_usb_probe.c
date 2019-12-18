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
struct device {int dummy; } ;
struct usb_interface {int num_altsetting; struct device dev; TYPE_3__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct i1480 {int buf_size; char* pre_fw_name; char* mac_fw_name; char* mac_fw_name_deprecate; char* phy_fw_name; struct i1480_usb* cmd_buf; int /*<<< orphan*/  cmd; int /*<<< orphan*/  wait_init_done; int /*<<< orphan*/ * rc_setup; int /*<<< orphan*/  read; int /*<<< orphan*/  write; struct device* dev; struct i1480_usb* evt_buf; } ;
struct i1480_usb {int /*<<< orphan*/  usb_dev; struct i1480 i1480; } ;
struct TYPE_5__ {int bNumEndpoints; int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int i1480_fw_upload (struct i1480*) ; 
 int /*<<< orphan*/  i1480_usb_cmd ; 
 int i1480_usb_create (struct i1480_usb*,struct usb_interface*) ; 
 int /*<<< orphan*/  i1480_usb_destroy (struct i1480_usb*) ; 
 int /*<<< orphan*/  i1480_usb_init (struct i1480_usb*) ; 
 int /*<<< orphan*/  i1480_usb_read ; 
 int /*<<< orphan*/  i1480_usb_wait_init_done ; 
 int /*<<< orphan*/  i1480_usb_write ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct i1480_usb*) ; 
 struct i1480_usb* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct i1480_usb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 
 int usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int i1480_usb_probe(struct usb_interface *iface, const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(iface);
	struct i1480_usb *i1480_usb;
	struct i1480 *i1480;
	struct device *dev = &iface->dev;
	int result;

	result = -ENODEV;
	if (iface->cur_altsetting->desc.bInterfaceNumber != 0) {
		dev_dbg(dev, "not attaching to iface %d\n",
			iface->cur_altsetting->desc.bInterfaceNumber);
		goto error;
	}
	if (iface->num_altsetting > 1 &&
			le16_to_cpu(udev->descriptor.idProduct) == 0xbabe) {
		/* Need altsetting #1 [HW QUIRK] or EP1 won't work */
		result = usb_set_interface(interface_to_usbdev(iface), 0, 1);
		if (result < 0)
			dev_warn(dev,
				 "can't set altsetting 1 on iface 0: %d\n",
				 result);
	}

	if (iface->cur_altsetting->desc.bNumEndpoints < 1)
		return -ENODEV;

	result = -ENOMEM;
	i1480_usb = kzalloc(sizeof(*i1480_usb), GFP_KERNEL);
	if (i1480_usb == NULL) {
		dev_err(dev, "Unable to allocate instance\n");
		goto error;
	}
	i1480_usb_init(i1480_usb);

	i1480 = &i1480_usb->i1480;
	i1480->buf_size = 512;
	i1480->cmd_buf = kmalloc_array(2, i1480->buf_size, GFP_KERNEL);
	if (i1480->cmd_buf == NULL) {
		dev_err(dev, "Cannot allocate transfer buffers\n");
		result = -ENOMEM;
		goto error_buf_alloc;
	}
	i1480->evt_buf = i1480->cmd_buf + i1480->buf_size;

	result = i1480_usb_create(i1480_usb, iface);
	if (result < 0) {
		dev_err(dev, "Cannot create instance: %d\n", result);
		goto error_create;
	}

	/* setup the fops and upload the firmware */
	i1480->pre_fw_name = "i1480-pre-phy-0.0.bin";
	i1480->mac_fw_name = "i1480-usb-0.0.bin";
	i1480->mac_fw_name_deprecate = "ptc-0.0.bin";
	i1480->phy_fw_name = "i1480-phy-0.0.bin";
	i1480->dev = &iface->dev;
	i1480->write = i1480_usb_write;
	i1480->read = i1480_usb_read;
	i1480->rc_setup = NULL;
	i1480->wait_init_done = i1480_usb_wait_init_done;
	i1480->cmd = i1480_usb_cmd;

	result = i1480_fw_upload(&i1480_usb->i1480);	/* the real thing */
	if (result >= 0) {
		usb_reset_device(i1480_usb->usb_dev);
		result = -ENODEV;	/* we don't want to bind to the iface */
	}
	i1480_usb_destroy(i1480_usb);
error_create:
	kfree(i1480->cmd_buf);
error_buf_alloc:
	kfree(i1480_usb);
error:
	return result;
}