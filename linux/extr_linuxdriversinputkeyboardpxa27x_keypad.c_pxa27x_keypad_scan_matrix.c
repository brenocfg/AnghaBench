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
typedef  int uint32_t ;
struct pxa27x_keypad_platform_data {int matrix_key_cols; int matrix_key_rows; } ;
struct pxa27x_keypad {int* matrix_key_state; int /*<<< orphan*/ * keycodes; int /*<<< orphan*/  row_shift; struct input_dev* input_dev; struct pxa27x_keypad_platform_data* pdata; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  new_state ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  KPAS ; 
 int /*<<< orphan*/  KPASMKP0 ; 
 int /*<<< orphan*/  KPASMKP1 ; 
 int /*<<< orphan*/  KPASMKP2 ; 
 int /*<<< orphan*/  KPASMKP3 ; 
 int KPASMKP_MKC_MASK ; 
 int KPAS_CP (int) ; 
 int KPAS_MUKP (int) ; 
 int KPAS_RP (int) ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int MAX_MATRIX_KEY_COLS ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int keypad_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pxa27x_keypad_scan_matrix(struct pxa27x_keypad *keypad)
{
	const struct pxa27x_keypad_platform_data *pdata = keypad->pdata;
	struct input_dev *input_dev = keypad->input_dev;
	int row, col, num_keys_pressed = 0;
	uint32_t new_state[MAX_MATRIX_KEY_COLS];
	uint32_t kpas = keypad_readl(KPAS);

	num_keys_pressed = KPAS_MUKP(kpas);

	memset(new_state, 0, sizeof(new_state));

	if (num_keys_pressed == 0)
		goto scan;

	if (num_keys_pressed == 1) {
		col = KPAS_CP(kpas);
		row = KPAS_RP(kpas);

		/* if invalid row/col, treat as no key pressed */
		if (col >= pdata->matrix_key_cols ||
		    row >= pdata->matrix_key_rows)
			goto scan;

		new_state[col] = (1 << row);
		goto scan;
	}

	if (num_keys_pressed > 1) {
		uint32_t kpasmkp0 = keypad_readl(KPASMKP0);
		uint32_t kpasmkp1 = keypad_readl(KPASMKP1);
		uint32_t kpasmkp2 = keypad_readl(KPASMKP2);
		uint32_t kpasmkp3 = keypad_readl(KPASMKP3);

		new_state[0] = kpasmkp0 & KPASMKP_MKC_MASK;
		new_state[1] = (kpasmkp0 >> 16) & KPASMKP_MKC_MASK;
		new_state[2] = kpasmkp1 & KPASMKP_MKC_MASK;
		new_state[3] = (kpasmkp1 >> 16) & KPASMKP_MKC_MASK;
		new_state[4] = kpasmkp2 & KPASMKP_MKC_MASK;
		new_state[5] = (kpasmkp2 >> 16) & KPASMKP_MKC_MASK;
		new_state[6] = kpasmkp3 & KPASMKP_MKC_MASK;
		new_state[7] = (kpasmkp3 >> 16) & KPASMKP_MKC_MASK;
	}
scan:
	for (col = 0; col < pdata->matrix_key_cols; col++) {
		uint32_t bits_changed;
		int code;

		bits_changed = keypad->matrix_key_state[col] ^ new_state[col];
		if (bits_changed == 0)
			continue;

		for (row = 0; row < pdata->matrix_key_rows; row++) {
			if ((bits_changed & (1 << row)) == 0)
				continue;

			code = MATRIX_SCAN_CODE(row, col, keypad->row_shift);

			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev, keypad->keycodes[code],
					 new_state[col] & (1 << row));
		}
	}
	input_sync(input_dev);
	memcpy(keypad->matrix_key_state, new_state, sizeof(new_state));
}