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
struct psmouse {unsigned char* packet; struct elantech_data* private; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
struct elantech_data {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 scalar_t__ elantech_is_buttonpad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,unsigned char) ; 

__attribute__((used)) static void elantech_input_sync_v4(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct elantech_data *etd = psmouse->private;
	unsigned char *packet = psmouse->packet;

	/* For clickpads map both buttons to BTN_LEFT */
	if (elantech_is_buttonpad(&etd->info))
		input_report_key(dev, BTN_LEFT, packet[0] & 0x03);
	else
		psmouse_report_standard_buttons(dev, packet[0]);

	input_mt_report_pointer_emulation(dev, true);
	input_sync(dev);
}