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
struct stmpe_keypad {scalar_t__* keymap; int rows; int cols; } ;

/* Variables and functions */
 scalar_t__ KEY_RESERVED ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMPE_KEYPAD_ROW_SHIFT ; 

__attribute__((used)) static void stmpe_keypad_fill_used_pins(struct stmpe_keypad *keypad,
					u32 used_rows, u32 used_cols)
{
	int row, col;

	for (row = 0; row < used_rows; row++) {
		for (col = 0; col < used_cols; col++) {
			int code = MATRIX_SCAN_CODE(row, col,
						    STMPE_KEYPAD_ROW_SHIFT);
			if (keypad->keymap[code] != KEY_RESERVED) {
				keypad->rows |= 1 << row;
				keypad->cols |= 1 << col;
			}
		}
	}
}