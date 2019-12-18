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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct tegra_kbc {unsigned short* keycode; unsigned int num_pressed_keys; int /*<<< orphan*/  current_keys; int /*<<< orphan*/  idev; scalar_t__ max_keys; scalar_t__ use_ghost_filter; scalar_t__ use_fn_map; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ KBC_KP_ENT0_0 ; 
 int KBC_MAX_KPENT ; 
 unsigned char KBC_ROW_SHIFT ; 
 unsigned short KEY_FN ; 
 unsigned char MATRIX_SCAN_CODE (unsigned int,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned short*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  tegra_kbc_report_pressed_keys (int /*<<< orphan*/ ,unsigned char*,unsigned short*,unsigned int) ; 
 int /*<<< orphan*/  tegra_kbc_report_released_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned short*,unsigned int) ; 

__attribute__((used)) static void tegra_kbc_report_keys(struct tegra_kbc *kbc)
{
	unsigned char scancodes[KBC_MAX_KPENT];
	unsigned short keycodes[KBC_MAX_KPENT];
	u32 val = 0;
	unsigned int i;
	unsigned int num_down = 0;
	bool fn_keypress = false;
	bool key_in_same_row = false;
	bool key_in_same_col = false;

	for (i = 0; i < KBC_MAX_KPENT; i++) {
		if ((i % 4) == 0)
			val = readl(kbc->mmio + KBC_KP_ENT0_0 + i);

		if (val & 0x80) {
			unsigned int col = val & 0x07;
			unsigned int row = (val >> 3) & 0x0f;
			unsigned char scancode =
				MATRIX_SCAN_CODE(row, col, KBC_ROW_SHIFT);

			scancodes[num_down] = scancode;
			keycodes[num_down] = kbc->keycode[scancode];
			/* If driver uses Fn map, do not report the Fn key. */
			if ((keycodes[num_down] == KEY_FN) && kbc->use_fn_map)
				fn_keypress = true;
			else
				num_down++;
		}

		val >>= 8;
	}

	/*
	 * Matrix keyboard designs are prone to keyboard ghosting.
	 * Ghosting occurs if there are 3 keys such that -
	 * any 2 of the 3 keys share a row, and any 2 of them share a column.
	 * If so ignore the key presses for this iteration.
	 */
	if (kbc->use_ghost_filter && num_down >= 3) {
		for (i = 0; i < num_down; i++) {
			unsigned int j;
			u8 curr_col = scancodes[i] & 0x07;
			u8 curr_row = scancodes[i] >> KBC_ROW_SHIFT;

			/*
			 * Find 2 keys such that one key is in the same row
			 * and the other is in the same column as the i-th key.
			 */
			for (j = i + 1; j < num_down; j++) {
				u8 col = scancodes[j] & 0x07;
				u8 row = scancodes[j] >> KBC_ROW_SHIFT;

				if (col == curr_col)
					key_in_same_col = true;
				if (row == curr_row)
					key_in_same_row = true;
			}
		}
	}

	/*
	 * If the platform uses Fn keymaps, translate keys on a Fn keypress.
	 * Function keycodes are max_keys apart from the plain keycodes.
	 */
	if (fn_keypress) {
		for (i = 0; i < num_down; i++) {
			scancodes[i] += kbc->max_keys;
			keycodes[i] = kbc->keycode[scancodes[i]];
		}
	}

	/* Ignore the key presses for this iteration? */
	if (key_in_same_col && key_in_same_row)
		return;

	tegra_kbc_report_released_keys(kbc->idev,
				       kbc->current_keys, kbc->num_pressed_keys,
				       keycodes, num_down);
	tegra_kbc_report_pressed_keys(kbc->idev, scancodes, keycodes, num_down);
	input_sync(kbc->idev);

	memcpy(kbc->current_keys, keycodes, sizeof(kbc->current_keys));
	kbc->num_pressed_keys = num_down;
}