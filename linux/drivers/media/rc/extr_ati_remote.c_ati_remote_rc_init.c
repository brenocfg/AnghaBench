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
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct rc_dev {char* driver_name; TYPE_1__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  allowed_protocols; struct ati_remote* priv; } ;
struct ati_remote {TYPE_2__* interface; int /*<<< orphan*/  udev; int /*<<< orphan*/  rc_phys; int /*<<< orphan*/  rc_name; struct rc_dev* rdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PROTO_BIT_OTHER ; 
 int /*<<< orphan*/  ati_remote_rc_close ; 
 int /*<<< orphan*/  ati_remote_rc_open ; 
 int /*<<< orphan*/  usb_to_input_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ati_remote_rc_init(struct ati_remote *ati_remote)
{
	struct rc_dev *rdev = ati_remote->rdev;

	rdev->priv = ati_remote;
	rdev->allowed_protocols = RC_PROTO_BIT_OTHER;
	rdev->driver_name = "ati_remote";

	rdev->open = ati_remote_rc_open;
	rdev->close = ati_remote_rc_close;

	rdev->device_name = ati_remote->rc_name;
	rdev->input_phys = ati_remote->rc_phys;

	usb_to_input_id(ati_remote->udev, &rdev->input_id);
	rdev->dev.parent = &ati_remote->interface->dev;
}