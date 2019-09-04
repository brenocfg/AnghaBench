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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct imx_keypad {int cols_en_mask; unsigned short* matrix_stable_state; int rows_en_mask; int /*<<< orphan*/ * keycodes; struct input_dev* input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MATRIX_ROW_SHIFT ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int MAX_MATRIX_KEY_COLS ; 
 int MAX_MATRIX_KEY_ROWS ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void imx_keypad_fire_events(struct imx_keypad *keypad,
				   unsigned short *matrix_volatile_state)
{
	struct input_dev *input_dev = keypad->input_dev;
	int row, col;

	for (col = 0; col < MAX_MATRIX_KEY_COLS; col++) {
		unsigned short bits_changed;
		int code;

		if ((keypad->cols_en_mask & (1 << col)) == 0)
			continue; /* Column is not enabled */

		bits_changed = keypad->matrix_stable_state[col] ^
						matrix_volatile_state[col];

		if (bits_changed == 0)
			continue; /* Column does not contain changes */

		for (row = 0; row < MAX_MATRIX_KEY_ROWS; row++) {
			if ((keypad->rows_en_mask & (1 << row)) == 0)
				continue; /* Row is not enabled */
			if ((bits_changed & (1 << row)) == 0)
				continue; /* Row does not contain changes */

			code = MATRIX_SCAN_CODE(row, col, MATRIX_ROW_SHIFT);
			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev, keypad->keycodes[code],
				matrix_volatile_state[col] & (1 << row));
			dev_dbg(&input_dev->dev, "Event code: %d, val: %d",
				keypad->keycodes[code],
				matrix_volatile_state[col] & (1 << row));
		}
	}
	input_sync(input_dev);
}