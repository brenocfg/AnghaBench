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
struct lpc32xx_kscan_drv {int* lastkeystates; unsigned int* keymap; int /*<<< orphan*/  row_shift; int /*<<< orphan*/  kscan_base; struct input_dev* input; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  LPC32XX_KS_DATA (int /*<<< orphan*/ ,int) ; 
 unsigned int MATRIX_SCAN_CODE (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_mod_states(struct lpc32xx_kscan_drv *kscandat, int col)
{
	struct input_dev *input = kscandat->input;
	unsigned row, changed, scancode, keycode;
	u8 key;

	key = readl(LPC32XX_KS_DATA(kscandat->kscan_base, col));
	changed = key ^ kscandat->lastkeystates[col];
	kscandat->lastkeystates[col] = key;

	for (row = 0; changed; row++, changed >>= 1) {
		if (changed & 1) {
			/* Key state changed, signal an event */
			scancode = MATRIX_SCAN_CODE(row, col,
						    kscandat->row_shift);
			keycode = kscandat->keymap[scancode];
			input_event(input, EV_MSC, MSC_SCAN, scancode);
			input_report_key(input, keycode, key & (1 << row));
		}
	}
}