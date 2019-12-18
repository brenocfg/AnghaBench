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
struct timer_list {int dummy; } ;
struct imx_keypad {int cols_en_mask; unsigned short* matrix_unstable_state; scalar_t__ stable_count; unsigned short* matrix_stable_state; scalar_t__ mmio_base; int /*<<< orphan*/  check_matrix_timer; } ;
typedef  int /*<<< orphan*/  matrix_volatile_state ;

/* Variables and functions */
 scalar_t__ IMX_KEYPAD_SCANS_FOR_STABILITY ; 
 unsigned short KBD_STAT_KDIE ; 
 unsigned short KBD_STAT_KDSC ; 
 unsigned short KBD_STAT_KPKD ; 
 unsigned short KBD_STAT_KPKR ; 
 unsigned short KBD_STAT_KRIE ; 
 unsigned short KBD_STAT_KRSS ; 
 scalar_t__ KPSR ; 
 int MAX_MATRIX_KEY_COLS ; 
 int /*<<< orphan*/  check_matrix_timer ; 
 struct imx_keypad* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_keypad_fire_events (struct imx_keypad*,unsigned short*) ; 
 int /*<<< orphan*/  imx_keypad_scan_matrix (struct imx_keypad*,unsigned short*) ; 
 scalar_t__ jiffies ; 
 struct imx_keypad* keypad ; 
 int /*<<< orphan*/  memcpy (unsigned short*,unsigned short*,int) ; 
 int /*<<< orphan*/  memset (unsigned short*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static void imx_keypad_check_for_events(struct timer_list *t)
{
	struct imx_keypad *keypad = from_timer(keypad, t, check_matrix_timer);
	unsigned short matrix_volatile_state[MAX_MATRIX_KEY_COLS];
	unsigned short reg_val;
	bool state_changed, is_zero_matrix;
	int i;

	memset(matrix_volatile_state, 0, sizeof(matrix_volatile_state));

	imx_keypad_scan_matrix(keypad, matrix_volatile_state);

	state_changed = false;
	for (i = 0; i < MAX_MATRIX_KEY_COLS; i++) {
		if ((keypad->cols_en_mask & (1 << i)) == 0)
			continue;

		if (keypad->matrix_unstable_state[i] ^ matrix_volatile_state[i]) {
			state_changed = true;
			break;
		}
	}

	/*
	 * If the matrix state is changed from the previous scan
	 *   (Re)Begin the debouncing process, saving the new state in
	 *    keypad->matrix_unstable_state.
	 * else
	 *   Increase the count of number of scans with a stable state.
	 */
	if (state_changed) {
		memcpy(keypad->matrix_unstable_state, matrix_volatile_state,
			sizeof(matrix_volatile_state));
		keypad->stable_count = 0;
	} else
		keypad->stable_count++;

	/*
	 * If the matrix is not as stable as we want reschedule scan
	 * in the near future.
	 */
	if (keypad->stable_count < IMX_KEYPAD_SCANS_FOR_STABILITY) {
		mod_timer(&keypad->check_matrix_timer,
			  jiffies + msecs_to_jiffies(10));
		return;
	}

	/*
	 * If the matrix state is stable, fire the events and save the new
	 * stable state. Note, if the matrix is kept stable for longer
	 * (keypad->stable_count > IMX_KEYPAD_SCANS_FOR_STABILITY) all
	 * events have already been generated.
	 */
	if (keypad->stable_count == IMX_KEYPAD_SCANS_FOR_STABILITY) {
		imx_keypad_fire_events(keypad, matrix_volatile_state);

		memcpy(keypad->matrix_stable_state, matrix_volatile_state,
			sizeof(matrix_volatile_state));
	}

	is_zero_matrix = true;
	for (i = 0; i < MAX_MATRIX_KEY_COLS; i++) {
		if (matrix_volatile_state[i] != 0) {
			is_zero_matrix = false;
			break;
		}
	}


	if (is_zero_matrix) {
		/*
		 * All keys have been released. Enable only the KDI
		 * interrupt for future key presses (clear the KDI
		 * status bit and its sync chain before that).
		 */
		reg_val = readw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KPKD | KBD_STAT_KDSC;
		writew(reg_val, keypad->mmio_base + KPSR);

		reg_val = readw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KDIE;
		reg_val &= ~KBD_STAT_KRIE;
		writew(reg_val, keypad->mmio_base + KPSR);
	} else {
		/*
		 * Some keys are still pressed. Schedule a rescan in
		 * attempt to detect multiple key presses and enable
		 * the KRI interrupt to react quickly to key release
		 * event.
		 */
		mod_timer(&keypad->check_matrix_timer,
			  jiffies + msecs_to_jiffies(60));

		reg_val = readw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KPKR | KBD_STAT_KRSS;
		writew(reg_val, keypad->mmio_base + KPSR);

		reg_val = readw(keypad->mmio_base + KPSR);
		reg_val |= KBD_STAT_KRIE;
		reg_val &= ~KBD_STAT_KDIE;
		writew(reg_val, keypad->mmio_base + KPSR);
	}
}