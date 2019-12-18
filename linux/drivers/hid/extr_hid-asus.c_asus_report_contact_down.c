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
typedef  int u8 ;
struct input_dev {int dummy; } ;
struct asus_drvdata {TYPE_1__* tp; struct input_dev* input; } ;
struct TYPE_2__ {int max_y; int contact_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int CONTACT_PRESSURE_MASK ; 
 int CONTACT_TOUCH_MAJOR_MASK ; 
 int CONTACT_X_MSB_MASK ; 
 int CONTACT_Y_MSB_MASK ; 
 int MAX_PRESSURE ; 
 int MAX_TOUCH_MAJOR ; 
 int MT_TOOL_PALM ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asus_report_contact_down(struct asus_drvdata *drvdat,
		int toolType, u8 *data)
{
	struct input_dev *input = drvdat->input;
	int touch_major, pressure, x, y;

	x = (data[0] & CONTACT_X_MSB_MASK) << 4 | data[1];
	y = drvdat->tp->max_y - ((data[0] & CONTACT_Y_MSB_MASK) << 8 | data[2]);

	input_report_abs(input, ABS_MT_POSITION_X, x);
	input_report_abs(input, ABS_MT_POSITION_Y, y);

	if (drvdat->tp->contact_size < 5)
		return;

	if (toolType == MT_TOOL_PALM) {
		touch_major = MAX_TOUCH_MAJOR;
		pressure = MAX_PRESSURE;
	} else {
		touch_major = (data[3] >> 4) & CONTACT_TOUCH_MAJOR_MASK;
		pressure = data[4] & CONTACT_PRESSURE_MASK;
	}

	input_report_abs(input, ABS_MT_TOUCH_MAJOR, touch_major);
	input_report_abs(input, ABS_MT_PRESSURE, pressure);
}