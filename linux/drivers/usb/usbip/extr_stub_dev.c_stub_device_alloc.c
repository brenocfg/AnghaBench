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
struct usb_device {int devnum; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  unusable; int /*<<< orphan*/  reset; int /*<<< orphan*/  shutdown; } ;
struct TYPE_6__ {int sockfd; TYPE_2__ eh_ops; int /*<<< orphan*/ * tcp_socket; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; int /*<<< orphan*/  side; } ;
struct stub_device {int devid; TYPE_3__ ud; int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  unlink_tx; int /*<<< orphan*/  unlink_free; int /*<<< orphan*/  priv_free; int /*<<< orphan*/  priv_tx; int /*<<< orphan*/  priv_init; int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {int busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDEV_ST_AVAILABLE ; 
 int /*<<< orphan*/  USBIP_STUB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct stub_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub_device_reset ; 
 int /*<<< orphan*/  stub_device_unusable ; 
 int /*<<< orphan*/  stub_shutdown_connection ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usbip_start_eh (TYPE_3__*) ; 

__attribute__((used)) static struct stub_device *stub_device_alloc(struct usb_device *udev)
{
	struct stub_device *sdev;
	int busnum = udev->bus->busnum;
	int devnum = udev->devnum;

	dev_dbg(&udev->dev, "allocating stub device");

	/* yes, it's a new device */
	sdev = kzalloc(sizeof(struct stub_device), GFP_KERNEL);
	if (!sdev)
		return NULL;

	sdev->udev = usb_get_dev(udev);

	/*
	 * devid is defined with devnum when this driver is first allocated.
	 * devnum may change later if a device is reset. However, devid never
	 * changes during a usbip connection.
	 */
	sdev->devid		= (busnum << 16) | devnum;
	sdev->ud.side		= USBIP_STUB;
	sdev->ud.status		= SDEV_ST_AVAILABLE;
	spin_lock_init(&sdev->ud.lock);
	sdev->ud.tcp_socket	= NULL;
	sdev->ud.sockfd		= -1;

	INIT_LIST_HEAD(&sdev->priv_init);
	INIT_LIST_HEAD(&sdev->priv_tx);
	INIT_LIST_HEAD(&sdev->priv_free);
	INIT_LIST_HEAD(&sdev->unlink_free);
	INIT_LIST_HEAD(&sdev->unlink_tx);
	spin_lock_init(&sdev->priv_lock);

	init_waitqueue_head(&sdev->tx_waitq);

	sdev->ud.eh_ops.shutdown = stub_shutdown_connection;
	sdev->ud.eh_ops.reset    = stub_device_reset;
	sdev->ud.eh_ops.unusable = stub_device_unusable;

	usbip_start_eh(&sdev->ud);

	dev_dbg(&udev->dev, "register new device\n");

	return sdev;
}