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
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void elo_process_data(struct input_dev *input, const u8 *data, int size)
{
	int press;

	input_report_abs(input, ABS_X, (data[3] << 8) | data[2]);
	input_report_abs(input, ABS_Y, (data[5] << 8) | data[4]);

	press = 0;
	if (data[1] & 0x80)
		press = (data[7] << 8) | data[6];
	input_report_abs(input, ABS_PRESSURE, press);

	if (data[1] & 0x03) {
		input_report_key(input, BTN_TOUCH, 1);
		input_sync(input);
	}

	if (data[1] & 0x04)
		input_report_key(input, BTN_TOUCH, 0);

	input_sync(input);
}