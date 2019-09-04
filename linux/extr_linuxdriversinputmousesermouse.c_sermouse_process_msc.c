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
struct sermouse {char* buf; int count; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void sermouse_process_msc(struct sermouse *sermouse, signed char data)
{
	struct input_dev *dev = sermouse->dev;
	signed char *buf = sermouse->buf;

	switch (sermouse->count) {

		case 0:
			if ((data & 0xf8) != 0x80)
				return;
			input_report_key(dev, BTN_LEFT,   !(data & 4));
			input_report_key(dev, BTN_RIGHT,  !(data & 1));
			input_report_key(dev, BTN_MIDDLE, !(data & 2));
			break;

		case 1:
		case 3:
			input_report_rel(dev, REL_X, data / 2);
			input_report_rel(dev, REL_Y, -buf[1]);
			buf[0] = data - data / 2;
			break;

		case 2:
		case 4:
			input_report_rel(dev, REL_X, buf[0]);
			input_report_rel(dev, REL_Y, buf[1] - data);
			buf[1] = data / 2;
			break;
	}

	input_sync(dev);

	if (++sermouse->count == 5)
		sermouse->count = 0;
}