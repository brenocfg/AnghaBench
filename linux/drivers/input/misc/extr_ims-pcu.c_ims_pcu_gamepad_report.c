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
typedef  int u32 ;
struct input_dev {int dummy; } ;
struct ims_pcu_gamepad {struct input_dev* input; } ;
struct ims_pcu {struct ims_pcu_gamepad* gamepad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void ims_pcu_gamepad_report(struct ims_pcu *pcu, u32 data)
{
	struct ims_pcu_gamepad *gamepad = pcu->gamepad;
	struct input_dev *input = gamepad->input;
	int x, y;

	x = !!(data & (1 << 14)) - !!(data & (1 << 13));
	y = !!(data & (1 << 12)) - !!(data & (1 << 11));

	input_report_abs(input, ABS_X, x);
	input_report_abs(input, ABS_Y, y);

	input_report_key(input, BTN_A, data & (1 << 7));
	input_report_key(input, BTN_B, data & (1 << 8));
	input_report_key(input, BTN_X, data & (1 << 9));
	input_report_key(input, BTN_Y, data & (1 << 10));
	input_report_key(input, BTN_START, data & (1 << 15));
	input_report_key(input, BTN_SELECT, data & (1 << 16));

	input_sync(input);
}