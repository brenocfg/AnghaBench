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
typedef  int u16 ;
struct input_dev {int dummy; } ;
struct egalax {int* data; struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int EGALAX_FORMAT_RESOLUTION_MASK ; 
 int EGALAX_FORMAT_TOUCH_BIT ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void egalax_process_data(struct egalax *egalax)
{
	struct input_dev *dev = egalax->input;
	u8 *data = egalax->data;
	u16 x, y;
	u8 shift;
	u8 mask;

	shift = 3 - ((data[0] & EGALAX_FORMAT_RESOLUTION_MASK) >> 1);
	mask = 0xff >> (shift + 1);

	x = (((u16)(data[1] & mask) << 7) | (data[2] & 0x7f)) << shift;
	y = (((u16)(data[3] & mask) << 7) | (data[4] & 0x7f)) << shift;

	input_report_key(dev, BTN_TOUCH, data[0] & EGALAX_FORMAT_TOUCH_BIT);
	input_report_abs(dev, ABS_X, x);
	input_report_abs(dev, ABS_Y, y);
	input_sync(dev);
}