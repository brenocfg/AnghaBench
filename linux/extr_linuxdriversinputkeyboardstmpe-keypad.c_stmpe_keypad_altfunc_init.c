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
typedef  unsigned int u8 ;
struct stmpe_keypad_variant {unsigned int col_gpios; unsigned int row_gpios; int max_cols; int max_rows; scalar_t__ set_pullup; } ;
struct stmpe_keypad {int cols; int rows; struct stmpe* stmpe; struct stmpe_keypad_variant* variant; } ;
struct stmpe {unsigned int* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE_BLOCK_KEYPAD ; 
 size_t STMPE_IDX_GPPUR_LSB ; 
 int __ffs (unsigned int) ; 
 int stmpe_reg_read (struct stmpe*,unsigned int) ; 
 int stmpe_reg_write (struct stmpe*,unsigned int,unsigned int) ; 
 int stmpe_set_altfunc (struct stmpe*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_keypad_altfunc_init(struct stmpe_keypad *keypad)
{
	const struct stmpe_keypad_variant *variant = keypad->variant;
	unsigned int col_gpios = variant->col_gpios;
	unsigned int row_gpios = variant->row_gpios;
	struct stmpe *stmpe = keypad->stmpe;
	u8 pureg = stmpe->regs[STMPE_IDX_GPPUR_LSB];
	unsigned int pins = 0;
	unsigned int pu_pins = 0;
	int ret;
	int i;

	/*
	 * Figure out which pins need to be set to the keypad alternate
	 * function.
	 *
	 * {cols,rows}_gpios are bitmasks of which pins on the chip can be used
	 * for the keypad.
	 *
	 * keypad->{cols,rows} are a bitmask of which pins (of the ones useable
	 * for the keypad) are used on the board.
	 */

	for (i = 0; i < variant->max_cols; i++) {
		int num = __ffs(col_gpios);

		if (keypad->cols & (1 << i)) {
			pins |= 1 << num;
			pu_pins |= 1 << num;
		}

		col_gpios &= ~(1 << num);
	}

	for (i = 0; i < variant->max_rows; i++) {
		int num = __ffs(row_gpios);

		if (keypad->rows & (1 << i))
			pins |= 1 << num;

		row_gpios &= ~(1 << num);
	}

	ret = stmpe_set_altfunc(stmpe, pins, STMPE_BLOCK_KEYPAD);
	if (ret)
		return ret;

	/*
	 * On STMPE24xx, set pin bias to pull-up on all keypad input
	 * pins (columns), this incidentally happen to be maximum 8 pins
	 * and placed at GPIO0-7 so only the LSB of the pull up register
	 * ever needs to be written.
	 */
	if (variant->set_pullup) {
		u8 val;

		ret = stmpe_reg_read(stmpe, pureg);
		if (ret)
			return ret;

		/* Do not touch unused pins, may be used for GPIO */
		val = ret & ~pu_pins;
		val |= pu_pins;

		ret = stmpe_reg_write(stmpe, pureg, val);
	}

	return 0;
}