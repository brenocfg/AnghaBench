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
typedef  size_t u8 ;
struct trackpoint_data {size_t variant_id; size_t firmware_id; } ;
struct ps2dev {TYPE_1__* serio; } ;
struct psmouse {char* name; int /*<<< orphan*/  vendor; struct trackpoint_data* private; TYPE_2__* dev; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  reconnect; struct ps2dev ps2dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  propbit; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_POINTING_STICK ; 
 int /*<<< orphan*/  TP_EXT_BTN ; 
 size_t TP_VARIANT_IBM ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trackpoint_data*) ; 
 struct trackpoint_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*,int) ; 
 int /*<<< orphan*/  psmouse_info (struct psmouse*,char*,int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 
 int /*<<< orphan*/  trackpoint_attr_group ; 
 int /*<<< orphan*/  trackpoint_defaults (struct trackpoint_data*) ; 
 int /*<<< orphan*/  trackpoint_disconnect ; 
 scalar_t__ trackpoint_power_on_reset (struct ps2dev*) ; 
 int trackpoint_read (struct ps2dev*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  trackpoint_reconnect ; 
 int trackpoint_start_protocol (struct psmouse*,size_t*,size_t*) ; 
 int /*<<< orphan*/  trackpoint_sync (struct psmouse*,int) ; 
 int /*<<< orphan*/ * trackpoint_variants ; 

int trackpoint_detect(struct psmouse *psmouse, bool set_properties)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	struct trackpoint_data *tp;
	u8 variant_id;
	u8 firmware_id;
	u8 button_info;
	int error;

	error = trackpoint_start_protocol(psmouse, &variant_id, &firmware_id);
	if (error)
		return error;

	if (!set_properties)
		return 0;

	tp = kzalloc(sizeof(*tp), GFP_KERNEL);
	if (!tp)
		return -ENOMEM;

	trackpoint_defaults(tp);
	tp->variant_id = variant_id;
	tp->firmware_id = firmware_id;

	psmouse->private = tp;

	psmouse->vendor = trackpoint_variants[variant_id];
	psmouse->name = "TrackPoint";

	psmouse->reconnect = trackpoint_reconnect;
	psmouse->disconnect = trackpoint_disconnect;

	if (variant_id != TP_VARIANT_IBM) {
		/* Newer variants do not support extended button query. */
		button_info = 0x33;
	} else {
		error = trackpoint_read(ps2dev, TP_EXT_BTN, &button_info);
		if (error) {
			psmouse_warn(psmouse,
				     "failed to get extended button data, assuming 3 buttons\n");
			button_info = 0x33;
		} else if (!button_info) {
			psmouse_warn(psmouse,
				     "got 0 in extended button data, assuming 3 buttons\n");
			button_info = 0x33;
		}
	}

	if ((button_info & 0x0f) >= 3)
		input_set_capability(psmouse->dev, EV_KEY, BTN_MIDDLE);

	__set_bit(INPUT_PROP_POINTER, psmouse->dev->propbit);
	__set_bit(INPUT_PROP_POINTING_STICK, psmouse->dev->propbit);

	if (variant_id != TP_VARIANT_IBM ||
	    trackpoint_power_on_reset(ps2dev) != 0) {
		/*
		 * Write defaults to TP if we did not reset the trackpoint.
		 */
		trackpoint_sync(psmouse, false);
	}

	error = device_add_group(&ps2dev->serio->dev, &trackpoint_attr_group);
	if (error) {
		psmouse_err(psmouse,
			    "failed to create sysfs attributes, error: %d\n",
			    error);
		kfree(psmouse->private);
		psmouse->private = NULL;
		return -1;
	}

	psmouse_info(psmouse,
		     "%s TrackPoint firmware: 0x%02x, buttons: %d/%d\n",
		     psmouse->vendor, firmware_id,
		     (button_info & 0xf0) >> 4, button_info & 0x0f);

	return 0;
}