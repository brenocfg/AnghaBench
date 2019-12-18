#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct dvb_usb_device* data; int /*<<< orphan*/  poll_slot_status; int /*<<< orphan*/  slot_ts_enable; int /*<<< orphan*/  slot_shutdown; int /*<<< orphan*/  slot_reset; int /*<<< orphan*/  write_cam_control; int /*<<< orphan*/  read_cam_control; int /*<<< orphan*/  write_attribute_mem; int /*<<< orphan*/  read_attribute_mem; int /*<<< orphan*/  owner; } ;
struct ttusb2_state {TYPE_1__ ca; int /*<<< orphan*/  ca_mutex; } ;
struct dvb_usb_device {struct ttusb2_state* priv; } ;
struct dvb_usb_adapter {int /*<<< orphan*/  dvb_adap; struct dvb_usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ci_dbg (char*) ; 
 int dvb_ca_en50221_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tt3650_ci_poll_slot_status ; 
 int /*<<< orphan*/  tt3650_ci_read_attribute_mem ; 
 int /*<<< orphan*/  tt3650_ci_read_cam_control ; 
 int /*<<< orphan*/  tt3650_ci_slot_reset ; 
 int /*<<< orphan*/  tt3650_ci_slot_shutdown ; 
 int /*<<< orphan*/  tt3650_ci_slot_ts_enable ; 
 int /*<<< orphan*/  tt3650_ci_write_attribute_mem ; 
 int /*<<< orphan*/  tt3650_ci_write_cam_control ; 

__attribute__((used)) static int tt3650_ci_init(struct dvb_usb_adapter *a)
{
	struct dvb_usb_device *d = a->dev;
	struct ttusb2_state *state = d->priv;
	int ret;

	ci_dbg("");

	mutex_init(&state->ca_mutex);

	state->ca.owner = THIS_MODULE;
	state->ca.read_attribute_mem = tt3650_ci_read_attribute_mem;
	state->ca.write_attribute_mem = tt3650_ci_write_attribute_mem;
	state->ca.read_cam_control = tt3650_ci_read_cam_control;
	state->ca.write_cam_control = tt3650_ci_write_cam_control;
	state->ca.slot_reset = tt3650_ci_slot_reset;
	state->ca.slot_shutdown = tt3650_ci_slot_shutdown;
	state->ca.slot_ts_enable = tt3650_ci_slot_ts_enable;
	state->ca.poll_slot_status = tt3650_ci_poll_slot_status;
	state->ca.data = d;

	ret = dvb_ca_en50221_init(&a->dvb_adap,
				  &state->ca,
				  /* flags */ 0,
				  /* n_slots */ 1);
	if (ret) {
		err("Cannot initialize CI: Error %d.", ret);
		memset(&state->ca, 0, sizeof(state->ca));
		return ret;
	}

	info("CI initialized.");

	return 0;
}