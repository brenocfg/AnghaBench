#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct streamzap_ir {TYPE_3__* usbdev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct device* dev; } ;
struct TYPE_6__ {struct device* parent; } ;
struct rc_dev {int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  allowed_protocols; struct streamzap_ir* priv; TYPE_2__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_7__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_STREAMZAP ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rc_dev *streamzap_init_rc_dev(struct streamzap_ir *sz)
{
	struct rc_dev *rdev;
	struct device *dev = sz->dev;
	int ret;

	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rdev) {
		dev_err(dev, "remote dev allocation failed\n");
		goto out;
	}

	snprintf(sz->name, sizeof(sz->name), "Streamzap PC Remote Infrared Receiver (%04x:%04x)",
		 le16_to_cpu(sz->usbdev->descriptor.idVendor),
		 le16_to_cpu(sz->usbdev->descriptor.idProduct));
	usb_make_path(sz->usbdev, sz->phys, sizeof(sz->phys));
	strlcat(sz->phys, "/input0", sizeof(sz->phys));

	rdev->device_name = sz->name;
	rdev->input_phys = sz->phys;
	usb_to_input_id(sz->usbdev, &rdev->input_id);
	rdev->dev.parent = dev;
	rdev->priv = sz;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->driver_name = DRIVER_NAME;
	rdev->map_name = RC_MAP_STREAMZAP;

	ret = rc_register_device(rdev);
	if (ret < 0) {
		dev_err(dev, "remote input device register failed\n");
		goto out;
	}

	return rdev;

out:
	rc_free_device(rdev);
	return NULL;
}