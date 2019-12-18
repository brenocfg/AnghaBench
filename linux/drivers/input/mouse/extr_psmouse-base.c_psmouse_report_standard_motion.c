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
typedef  int u8 ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 

void psmouse_report_standard_motion(struct input_dev *dev, u8 *packet)
{
	int x, y;

	x = packet[1] ? packet[1] - ((packet[0] << 4) & 0x100) : 0;
	y = packet[2] ? packet[2] - ((packet[0] << 3) & 0x100) : 0;

	input_report_rel(dev, REL_X, x);
	input_report_rel(dev, REL_Y, -y);
}