#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct rc_dev {int /*<<< orphan*/  scancode_mask; struct dvb_usb_device* priv; TYPE_2__ dev; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; int /*<<< orphan*/  input_id; int /*<<< orphan*/  allowed_protocols; int /*<<< orphan*/  change_protocol; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; } ;
struct TYPE_9__ {int rc_interval; scalar_t__ bulk_mode; int /*<<< orphan*/  rc_query; int /*<<< orphan*/  scancode_mask; int /*<<< orphan*/  allowed_protos; int /*<<< orphan*/  change_protocol; int /*<<< orphan*/  rc_codes; int /*<<< orphan*/  module_name; int /*<<< orphan*/  driver_type; } ;
struct TYPE_10__ {TYPE_3__ core; } ;
struct TYPE_11__ {TYPE_4__ rc; } ;
struct dvb_usb_device {int /*<<< orphan*/  rc_query_work; TYPE_5__ props; struct rc_dev* rc_dev; int /*<<< orphan*/ * input_dev; TYPE_6__* udev; int /*<<< orphan*/  rc_phys; TYPE_1__* desc; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_usb_read_remote_control ; 
 int /*<<< orphan*/  info (char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_to_input_id (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc_core_dvb_usb_remote_init(struct dvb_usb_device *d)
{
	int err, rc_interval;
	struct rc_dev *dev;

	dev = rc_allocate_device(d->props.rc.core.driver_type);
	if (!dev)
		return -ENOMEM;

	dev->driver_name = d->props.rc.core.module_name;
	dev->map_name = d->props.rc.core.rc_codes;
	dev->change_protocol = d->props.rc.core.change_protocol;
	dev->allowed_protocols = d->props.rc.core.allowed_protos;
	usb_to_input_id(d->udev, &dev->input_id);
	dev->device_name = d->desc->name;
	dev->input_phys = d->rc_phys;
	dev->dev.parent = &d->udev->dev;
	dev->priv = d;
	dev->scancode_mask = d->props.rc.core.scancode_mask;

	err = rc_register_device(dev);
	if (err < 0) {
		rc_free_device(dev);
		return err;
	}

	d->input_dev = NULL;
	d->rc_dev = dev;

	if (!d->props.rc.core.rc_query || d->props.rc.core.bulk_mode)
		return 0;

	/* Polling mode - initialize a work queue for handling it */
	INIT_DELAYED_WORK(&d->rc_query_work, dvb_usb_read_remote_control);

	rc_interval = d->props.rc.core.rc_interval;

	info("schedule remote query interval to %d msecs.", rc_interval);
	schedule_delayed_work(&d->rc_query_work,
			      msecs_to_jiffies(rc_interval));

	return 0;
}