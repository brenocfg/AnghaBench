#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct usb_xpad {int mapping; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  unsigned char __u16 ;
typedef  unsigned char __s16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_MODE ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_THUMBL ; 
 int /*<<< orphan*/  BTN_THUMBR ; 
 int /*<<< orphan*/  BTN_TL ; 
 int /*<<< orphan*/  BTN_TL2 ; 
 int /*<<< orphan*/  BTN_TR ; 
 int /*<<< orphan*/  BTN_TR2 ; 
 int /*<<< orphan*/  BTN_TRIGGER_HAPPY1 ; 
 int /*<<< orphan*/  BTN_TRIGGER_HAPPY2 ; 
 int /*<<< orphan*/  BTN_TRIGGER_HAPPY3 ; 
 int /*<<< orphan*/  BTN_TRIGGER_HAPPY4 ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int MAP_DPAD_TO_BUTTONS ; 
 int MAP_STICKS_TO_NULL ; 
 int MAP_TRIGGERS_TO_BUTTONS ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpadone_ack_mode_report (struct usb_xpad*,unsigned char) ; 

__attribute__((used)) static void xpadone_process_packet(struct usb_xpad *xpad, u16 cmd, unsigned char *data)
{
	struct input_dev *dev = xpad->dev;

	/* the xbox button has its own special report */
	if (data[0] == 0X07) {
		/*
		 * The Xbox One S controller requires these reports to be
		 * acked otherwise it continues sending them forever and
		 * won't report further mode button events.
		 */
		if (data[1] == 0x30)
			xpadone_ack_mode_report(xpad, data[2]);

		input_report_key(dev, BTN_MODE, data[4] & 0x01);
		input_sync(dev);
		return;
	}
	/* check invalid packet */
	else if (data[0] != 0X20)
		return;

	/* menu/view buttons */
	input_report_key(dev, BTN_START,  data[4] & 0x04);
	input_report_key(dev, BTN_SELECT, data[4] & 0x08);

	/* buttons A,B,X,Y */
	input_report_key(dev, BTN_A,	data[4] & 0x10);
	input_report_key(dev, BTN_B,	data[4] & 0x20);
	input_report_key(dev, BTN_X,	data[4] & 0x40);
	input_report_key(dev, BTN_Y,	data[4] & 0x80);

	/* digital pad */
	if (xpad->mapping & MAP_DPAD_TO_BUTTONS) {
		/* dpad as buttons (left, right, up, down) */
		input_report_key(dev, BTN_TRIGGER_HAPPY1, data[5] & 0x04);
		input_report_key(dev, BTN_TRIGGER_HAPPY2, data[5] & 0x08);
		input_report_key(dev, BTN_TRIGGER_HAPPY3, data[5] & 0x01);
		input_report_key(dev, BTN_TRIGGER_HAPPY4, data[5] & 0x02);
	} else {
		input_report_abs(dev, ABS_HAT0X,
				 !!(data[5] & 0x08) - !!(data[5] & 0x04));
		input_report_abs(dev, ABS_HAT0Y,
				 !!(data[5] & 0x02) - !!(data[5] & 0x01));
	}

	/* TL/TR */
	input_report_key(dev, BTN_TL,	data[5] & 0x10);
	input_report_key(dev, BTN_TR,	data[5] & 0x20);

	/* stick press left/right */
	input_report_key(dev, BTN_THUMBL, data[5] & 0x40);
	input_report_key(dev, BTN_THUMBR, data[5] & 0x80);

	if (!(xpad->mapping & MAP_STICKS_TO_NULL)) {
		/* left stick */
		input_report_abs(dev, ABS_X,
				 (__s16) le16_to_cpup((__le16 *)(data + 10)));
		input_report_abs(dev, ABS_Y,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 12)));

		/* right stick */
		input_report_abs(dev, ABS_RX,
				 (__s16) le16_to_cpup((__le16 *)(data + 14)));
		input_report_abs(dev, ABS_RY,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 16)));
	}

	/* triggers left/right */
	if (xpad->mapping & MAP_TRIGGERS_TO_BUTTONS) {
		input_report_key(dev, BTN_TL2,
				 (__u16) le16_to_cpup((__le16 *)(data + 6)));
		input_report_key(dev, BTN_TR2,
				 (__u16) le16_to_cpup((__le16 *)(data + 8)));
	} else {
		input_report_abs(dev, ABS_Z,
				 (__u16) le16_to_cpup((__le16 *)(data + 6)));
		input_report_abs(dev, ABS_RZ,
				 (__u16) le16_to_cpup((__le16 *)(data + 8)));
	}

	input_sync(dev);
}