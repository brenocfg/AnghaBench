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
typedef  int u32 ;
struct rc_dev {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,char*,char*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ir_mce_kbd_process_mouse_data(struct rc_dev *dev, u32 scancode)
{
	/* raw mouse coordinates */
	u8 xdata = (scancode >> 7) & 0x7f;
	u8 ydata = (scancode >> 14) & 0x7f;
	int x, y;
	/* mouse buttons */
	bool right = scancode & 0x40;
	bool left  = scancode & 0x20;

	if (xdata & 0x40)
		x = -((~xdata & 0x7f) + 1);
	else
		x = xdata;

	if (ydata & 0x40)
		y = -((~ydata & 0x7f) + 1);
	else
		y = ydata;

	dev_dbg(&dev->dev, "mouse: x = %d, y = %d, btns = %s%s\n",
		x, y, left ? "L" : "", right ? "R" : "");

	input_report_rel(dev->input_dev, REL_X, x);
	input_report_rel(dev->input_dev, REL_Y, y);

	input_report_key(dev->input_dev, BTN_LEFT, left);
	input_report_key(dev->input_dev, BTN_RIGHT, right);
}