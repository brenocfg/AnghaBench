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
struct navpoint {int* data; int /*<<< orphan*/  dev; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void navpoint_packet(struct navpoint *navpoint)
{
	int finger;
	int gesture;
	int x, y, z;

	switch (navpoint->data[0]) {
	case 0xff:	/* Garbage (packet?) between reset and Hello packet */
	case 0x00:	/* Module 0, NULL packet */
		break;

	case 0x0e:	/* Module 0, Absolute packet */
		finger = (navpoint->data[1] & 0x01);
		gesture = (navpoint->data[1] & 0x02);
		x = ((navpoint->data[2] & 0x1f) << 8) | navpoint->data[3];
		y = ((navpoint->data[4] & 0x1f) << 8) | navpoint->data[5];
		z = navpoint->data[6];
		input_report_key(navpoint->input, BTN_TOUCH, finger);
		input_report_abs(navpoint->input, ABS_X, x);
		input_report_abs(navpoint->input, ABS_Y, y);
		input_report_abs(navpoint->input, ABS_PRESSURE, z);
		input_report_key(navpoint->input, BTN_TOOL_FINGER, finger);
		input_report_key(navpoint->input, BTN_LEFT, gesture);
		input_sync(navpoint->input);
		break;

	case 0x19:	/* Module 0, Hello packet */
		if ((navpoint->data[1] & 0xf0) == 0x10)
			break;
		/* FALLTHROUGH */
	default:
		dev_warn(navpoint->dev,
			 "spurious packet: data=0x%02x,0x%02x,...\n",
			 navpoint->data[0], navpoint->data[1]);
		break;
	}
}