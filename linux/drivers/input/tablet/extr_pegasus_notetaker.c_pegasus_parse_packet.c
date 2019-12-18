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
typedef  int /*<<< orphan*/  u16 ;
struct pegasus {unsigned char* data; TYPE_1__* usbdev; int /*<<< orphan*/  init; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
#define  BATTERY_GOOD 131 
#define  BATTERY_LOW 130 
#define  BATTERY_NO_REPORT 129 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 unsigned char BUTTON_PRESSED ; 
 unsigned char PEN_BUTTON_PRESSED ; 
 unsigned char PEN_TIP ; 
#define  SPECIAL_COMMAND 128 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pegasus_parse_packet(struct pegasus *pegasus)
{
	unsigned char *data = pegasus->data;
	struct input_dev *dev = pegasus->dev;
	u16 x, y;

	switch (data[0]) {
	case SPECIAL_COMMAND:
		/* device button pressed */
		if (data[1] == BUTTON_PRESSED)
			schedule_work(&pegasus->init);

		break;

	/* xy data */
	case BATTERY_LOW:
		dev_warn_once(&dev->dev, "Pen battery low\n");
		/* fall through */

	case BATTERY_NO_REPORT:
	case BATTERY_GOOD:
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);

		/* pen-up event */
		if (x == 0 && y == 0)
			break;

		input_report_key(dev, BTN_TOUCH, data[1] & PEN_TIP);
		input_report_key(dev, BTN_RIGHT, data[1] & PEN_BUTTON_PRESSED);
		input_report_key(dev, BTN_TOOL_PEN, 1);
		input_report_abs(dev, ABS_X, (s16)x);
		input_report_abs(dev, ABS_Y, y);

		input_sync(dev);
		break;

	default:
		dev_warn_once(&pegasus->usbdev->dev,
			      "unknown answer from device\n");
	}
}