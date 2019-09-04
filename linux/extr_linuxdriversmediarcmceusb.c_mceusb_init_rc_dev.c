#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  idVendor; int /*<<< orphan*/  idProduct; } ;
struct usb_device {TYPE_3__ descriptor; } ;
struct TYPE_5__ {struct device* parent; } ;
struct rc_dev {int timeout; int max_timeout; scalar_t__ map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  s_carrier_report; int /*<<< orphan*/  s_learning_mode; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  s_tx_mask; int /*<<< orphan*/  s_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/  allowed_protocols; struct mceusb_dev* priv; TYPE_1__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; } ;
struct TYPE_6__ {scalar_t__ rx2; int /*<<< orphan*/  no_tx; } ;
struct mceusb_dev {size_t model; TYPE_2__ flags; struct usb_device* usbdev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_8__ {char* name; scalar_t__ rc_map; int /*<<< orphan*/  broken_irtimeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int IR_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  MCE_TIME_UNIT ; 
 int MS_TO_NS (int) ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 scalar_t__ RC_MAP_HAUPPAUGE ; 
 scalar_t__ RC_MAP_PINNACLE_PCTV_HD ; 
 scalar_t__ RC_MAP_RC6_MCE ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 int /*<<< orphan*/  US_TO_NS (int /*<<< orphan*/ ) ; 
#define  VENDOR_HAUPPAUGE 129 
#define  VENDOR_PCTV 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_4__* mceusb_model ; 
 int /*<<< orphan*/  mceusb_set_rx_carrier_report ; 
 int /*<<< orphan*/  mceusb_set_rx_wideband ; 
 int /*<<< orphan*/  mceusb_set_timeout ; 
 int /*<<< orphan*/  mceusb_set_tx_carrier ; 
 int /*<<< orphan*/  mceusb_set_tx_mask ; 
 int /*<<< orphan*/  mceusb_tx_ir ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rc_dev *mceusb_init_rc_dev(struct mceusb_dev *ir)
{
	struct usb_device *udev = ir->usbdev;
	struct device *dev = ir->dev;
	struct rc_dev *rc;
	int ret;

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rc) {
		dev_err(dev, "remote dev allocation failed");
		goto out;
	}

	snprintf(ir->name, sizeof(ir->name), "%s (%04x:%04x)",
		 mceusb_model[ir->model].name ?
			mceusb_model[ir->model].name :
			"Media Center Ed. eHome Infrared Remote Transceiver",
		 le16_to_cpu(ir->usbdev->descriptor.idVendor),
		 le16_to_cpu(ir->usbdev->descriptor.idProduct));

	usb_make_path(ir->usbdev, ir->phys, sizeof(ir->phys));

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	usb_to_input_id(ir->usbdev, &rc->input_id);
	rc->dev.parent = dev;
	rc->priv = ir;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->min_timeout = US_TO_NS(MCE_TIME_UNIT);
	rc->timeout = MS_TO_NS(100);
	if (!mceusb_model[ir->model].broken_irtimeout) {
		rc->s_timeout = mceusb_set_timeout;
		rc->max_timeout = 10 * IR_DEFAULT_TIMEOUT;
	} else {
		/*
		 * If we can't set the timeout using CMD_SETIRTIMEOUT, we can
		 * rely on software timeouts for timeouts < 100ms.
		 */
		rc->max_timeout = rc->timeout;
	}
	if (!ir->flags.no_tx) {
		rc->s_tx_mask = mceusb_set_tx_mask;
		rc->s_tx_carrier = mceusb_set_tx_carrier;
		rc->tx_ir = mceusb_tx_ir;
	}
	if (ir->flags.rx2 > 0) {
		rc->s_learning_mode = mceusb_set_rx_wideband;
		rc->s_carrier_report = mceusb_set_rx_carrier_report;
	}
	rc->driver_name = DRIVER_NAME;

	switch (le16_to_cpu(udev->descriptor.idVendor)) {
	case VENDOR_HAUPPAUGE:
		rc->map_name = RC_MAP_HAUPPAUGE;
		break;
	case VENDOR_PCTV:
		rc->map_name = RC_MAP_PINNACLE_PCTV_HD;
		break;
	default:
		rc->map_name = RC_MAP_RC6_MCE;
	}
	if (mceusb_model[ir->model].rc_map)
		rc->map_name = mceusb_model[ir->model].rc_map;

	ret = rc_register_device(rc);
	if (ret < 0) {
		dev_err(dev, "remote dev registration failed");
		goto out;
	}

	return rc;

out:
	rc_free_device(rc);
	return NULL;
}