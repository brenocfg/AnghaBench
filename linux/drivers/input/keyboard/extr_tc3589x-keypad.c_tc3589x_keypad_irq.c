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
struct tc_keypad {int /*<<< orphan*/  input; int /*<<< orphan*/ * keymap; struct tc3589x* tc3589x; } ;
struct tc3589x {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KP_EVCODE_COL_MASK ; 
 int KP_EVCODE_ROW_MASK ; 
 int KP_RELEASE_EVT_MASK ; 
 int KP_ROW_SHIFT ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int TC35893_DATA_REGS ; 
 int TC35893_KEYCODE_FIFO_CLEAR ; 
 int TC35893_KEYCODE_FIFO_EMPTY ; 
 int /*<<< orphan*/  TC35893_KEYPAD_ROW_SHIFT ; 
 int /*<<< orphan*/  TC3589x_EVTCODE_FIFO ; 
 int TC3589x_EVT_INT ; 
 int TC3589x_EVT_INT_CLR ; 
 int TC3589x_EVT_LOSS_INT ; 
 int /*<<< orphan*/  TC3589x_KBDIC ; 
 int /*<<< orphan*/  TC3589x_KBDMSK ; 
 int TC3589x_KBD_INT_CLR ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int tc3589x_reg_read (struct tc3589x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc3589x_set_bits (struct tc3589x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t tc3589x_keypad_irq(int irq, void *dev)
{
	struct tc_keypad *keypad = dev;
	struct tc3589x *tc3589x = keypad->tc3589x;
	u8 i, row_index, col_index, kbd_code, up;
	u8 code;

	for (i = 0; i < TC35893_DATA_REGS * 2; i++) {
		kbd_code = tc3589x_reg_read(tc3589x, TC3589x_EVTCODE_FIFO);

		/* loop till fifo is empty and no more keys are pressed */
		if (kbd_code == TC35893_KEYCODE_FIFO_EMPTY ||
				kbd_code == TC35893_KEYCODE_FIFO_CLEAR)
			continue;

		/* valid key is found */
		col_index = kbd_code & KP_EVCODE_COL_MASK;
		row_index = (kbd_code & KP_EVCODE_ROW_MASK) >> KP_ROW_SHIFT;
		code = MATRIX_SCAN_CODE(row_index, col_index,
						TC35893_KEYPAD_ROW_SHIFT);
		up = kbd_code & KP_RELEASE_EVT_MASK;

		input_event(keypad->input, EV_MSC, MSC_SCAN, code);
		input_report_key(keypad->input, keypad->keymap[code], !up);
		input_sync(keypad->input);
	}

	/* clear IRQ */
	tc3589x_set_bits(tc3589x, TC3589x_KBDIC,
			0x0, TC3589x_EVT_INT_CLR | TC3589x_KBD_INT_CLR);
	/* enable IRQ */
	tc3589x_set_bits(tc3589x, TC3589x_KBDMSK,
			0x0, TC3589x_EVT_LOSS_INT | TC3589x_EVT_INT);

	return IRQ_HANDLED;
}