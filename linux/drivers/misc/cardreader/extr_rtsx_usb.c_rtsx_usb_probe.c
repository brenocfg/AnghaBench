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
struct usb_interface {int needs_remote_wakeup; int /*<<< orphan*/  dev; } ;
struct usb_device_id {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {int /*<<< orphan*/  devnum; TYPE_1__* bus; } ;
struct rtsx_ucr {int /*<<< orphan*/  iobuf_dma; scalar_t__ iobuf; struct usb_device* pusb_dev; int /*<<< orphan*/  sg_timer; struct usb_interface* pusb_intf; int /*<<< orphan*/  dev_mutex; scalar_t__ rsp_buf; scalar_t__ cmd_buf; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOBUF_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtsx_ucr* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int mfd_add_hotplug_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsx_usb_cells ; 
 int rtsx_usb_init_chip (struct rtsx_ucr*) ; 
 int /*<<< orphan*/  rtsx_usb_sg_timed_out ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_enable_autosuspend (struct usb_device*) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct rtsx_ucr*) ; 

__attribute__((used)) static int rtsx_usb_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	struct rtsx_ucr *ucr;
	int ret;

	dev_dbg(&intf->dev,
		": Realtek USB Card Reader found at bus %03d address %03d\n",
		 usb_dev->bus->busnum, usb_dev->devnum);

	ucr = devm_kzalloc(&intf->dev, sizeof(*ucr), GFP_KERNEL);
	if (!ucr)
		return -ENOMEM;

	ucr->pusb_dev = usb_dev;

	ucr->iobuf = usb_alloc_coherent(ucr->pusb_dev, IOBUF_SIZE,
			GFP_KERNEL, &ucr->iobuf_dma);
	if (!ucr->iobuf)
		return -ENOMEM;

	usb_set_intfdata(intf, ucr);

	ucr->vendor_id = id->idVendor;
	ucr->product_id = id->idProduct;
	ucr->cmd_buf = ucr->rsp_buf = ucr->iobuf;

	mutex_init(&ucr->dev_mutex);

	ucr->pusb_intf = intf;

	/* initialize */
	ret = rtsx_usb_init_chip(ucr);
	if (ret)
		goto out_init_fail;

	/* initialize USB SG transfer timer */
	timer_setup(&ucr->sg_timer, rtsx_usb_sg_timed_out, 0);

	ret = mfd_add_hotplug_devices(&intf->dev, rtsx_usb_cells,
				      ARRAY_SIZE(rtsx_usb_cells));
	if (ret)
		goto out_init_fail;

#ifdef CONFIG_PM
	intf->needs_remote_wakeup = 1;
	usb_enable_autosuspend(usb_dev);
#endif

	return 0;

out_init_fail:
	usb_free_coherent(ucr->pusb_dev, IOBUF_SIZE, ucr->iobuf,
			ucr->iobuf_dma);
	return ret;
}