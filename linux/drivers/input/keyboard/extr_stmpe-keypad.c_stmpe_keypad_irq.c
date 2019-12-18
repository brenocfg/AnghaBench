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
struct stmpe_keypad_variant {int num_normal_data; } ;
struct stmpe_keypad {int /*<<< orphan*/ * keymap; struct stmpe_keypad_variant* variant; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int MAX_NUM_DATA ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  STMPE_KEYPAD_ROW_SHIFT ; 
 int STMPE_KPC_DATA_COL ; 
 int STMPE_KPC_DATA_NOKEY_MASK ; 
 int STMPE_KPC_DATA_ROW ; 
 int STMPE_KPC_DATA_UP ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int stmpe_keypad_read_data (struct stmpe_keypad*,int*) ; 

__attribute__((used)) static irqreturn_t stmpe_keypad_irq(int irq, void *dev)
{
	struct stmpe_keypad *keypad = dev;
	struct input_dev *input = keypad->input;
	const struct stmpe_keypad_variant *variant = keypad->variant;
	u8 fifo[MAX_NUM_DATA];
	int ret;
	int i;

	ret = stmpe_keypad_read_data(keypad, fifo);
	if (ret < 0)
		return IRQ_NONE;

	for (i = 0; i < variant->num_normal_data; i++) {
		u8 data = fifo[i];
		int row = (data & STMPE_KPC_DATA_ROW) >> 3;
		int col = data & STMPE_KPC_DATA_COL;
		int code = MATRIX_SCAN_CODE(row, col, STMPE_KEYPAD_ROW_SHIFT);
		bool up = data & STMPE_KPC_DATA_UP;

		if ((data & STMPE_KPC_DATA_NOKEY_MASK)
			== STMPE_KPC_DATA_NOKEY_MASK)
			continue;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_report_key(input, keypad->keymap[code], !up);
		input_sync(input);
	}

	return IRQ_HANDLED;
}