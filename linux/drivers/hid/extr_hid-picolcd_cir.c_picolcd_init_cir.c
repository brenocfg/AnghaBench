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
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {int /*<<< orphan*/  rx_resolution; int /*<<< orphan*/  timeout; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; TYPE_2__ dev; TYPE_1__ input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  allowed_protocols; struct picolcd_data* priv; } ;
struct picolcd_data {struct rc_dev* rc_dev; TYPE_3__* hdev; } ;
struct hid_report {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bus; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MS_TO_NS (int) ; 
 int /*<<< orphan*/  PICOLCD_NAME ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_RC6_MCE ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  picolcd_cir_close ; 
 int /*<<< orphan*/  picolcd_cir_open ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 

int picolcd_init_cir(struct picolcd_data *data, struct hid_report *report)
{
	struct rc_dev *rdev;
	int ret = 0;

	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rdev)
		return -ENOMEM;

	rdev->priv             = data;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->open             = picolcd_cir_open;
	rdev->close            = picolcd_cir_close;
	rdev->device_name      = data->hdev->name;
	rdev->input_phys       = data->hdev->phys;
	rdev->input_id.bustype = data->hdev->bus;
	rdev->input_id.vendor  = data->hdev->vendor;
	rdev->input_id.product = data->hdev->product;
	rdev->input_id.version = data->hdev->version;
	rdev->dev.parent       = &data->hdev->dev;
	rdev->driver_name      = PICOLCD_NAME;
	rdev->map_name         = RC_MAP_RC6_MCE;
	rdev->timeout          = MS_TO_NS(100);
	rdev->rx_resolution    = US_TO_NS(1);

	ret = rc_register_device(rdev);
	if (ret)
		goto err;
	data->rc_dev = rdev;
	return 0;

err:
	rc_free_device(rdev);
	return ret;
}