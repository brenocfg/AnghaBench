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
struct touchscreen_data {int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void micro_ts_receive(void *data, int len, unsigned char *msg)
{
	struct touchscreen_data *ts = data;

	if (len == 4) {
		input_report_abs(ts->input, ABS_X,
				 be16_to_cpup((__be16 *) &msg[2]));
		input_report_abs(ts->input, ABS_Y,
				 be16_to_cpup((__be16 *) &msg[0]));
		input_report_key(ts->input, BTN_TOUCH, 1);
		input_sync(ts->input);
	} else if (len == 0) {
		input_report_abs(ts->input, ABS_X, 0);
		input_report_abs(ts->input, ABS_Y, 0);
		input_report_key(ts->input, BTN_TOUCH, 0);
		input_sync(ts->input);
	}
}