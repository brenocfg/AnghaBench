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
typedef  int /*<<< orphan*/  u8 ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_report_standard_motion (struct input_dev*,int /*<<< orphan*/ *) ; 

void psmouse_report_standard_packet(struct input_dev *dev, u8 *packet)
{
	psmouse_report_standard_buttons(dev, packet[0]);
	psmouse_report_standard_motion(dev, packet);
}