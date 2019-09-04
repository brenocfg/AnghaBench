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
struct samsung_keypad {unsigned int cols; unsigned int* row_state; unsigned int rows; struct input_dev* input_dev; int /*<<< orphan*/ * keycodes; int /*<<< orphan*/  row_shift; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 unsigned int MATRIX_SCAN_CODE (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 

__attribute__((used)) static bool samsung_keypad_report(struct samsung_keypad *keypad,
				  unsigned int *row_state)
{
	struct input_dev *input_dev = keypad->input_dev;
	unsigned int changed;
	unsigned int pressed;
	unsigned int key_down = 0;
	unsigned int val;
	unsigned int col, row;

	for (col = 0; col < keypad->cols; col++) {
		changed = row_state[col] ^ keypad->row_state[col];
		key_down |= row_state[col];
		if (!changed)
			continue;

		for (row = 0; row < keypad->rows; row++) {
			if (!(changed & (1 << row)))
				continue;

			pressed = row_state[col] & (1 << row);

			dev_dbg(&keypad->input_dev->dev,
				"key %s, row: %d, col: %d\n",
				pressed ? "pressed" : "released", row, col);

			val = MATRIX_SCAN_CODE(row, col, keypad->row_shift);

			input_event(input_dev, EV_MSC, MSC_SCAN, val);
			input_report_key(input_dev,
					keypad->keycodes[val], pressed);
		}
		input_sync(keypad->input_dev);
	}

	memcpy(keypad->row_state, row_state, sizeof(keypad->row_state));

	return key_down;
}