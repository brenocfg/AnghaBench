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
typedef  int uint8_t ;
struct input_dev {unsigned short* keycode; } ;
struct cros_ec_keyb {int cols; int rows; int* old_kb_state; struct input_dev* idev; int /*<<< orphan*/  dev; int /*<<< orphan*/  row_shift; scalar_t__ ghost_filter; } ;

/* Variables and functions */
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cros_ec_keyb_has_ghosting (struct cros_ec_keyb*,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned short const,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cros_ec_keyb_process(struct cros_ec_keyb *ckdev,
			 uint8_t *kb_state, int len)
{
	struct input_dev *idev = ckdev->idev;
	int col, row;
	int new_state;
	int old_state;

	if (ckdev->ghost_filter && cros_ec_keyb_has_ghosting(ckdev, kb_state)) {
		/*
		 * Simple-minded solution: ignore this state. The obvious
		 * improvement is to only ignore changes to keys involved in
		 * the ghosting, but process the other changes.
		 */
		dev_dbg(ckdev->dev, "ghosting found\n");
		return;
	}

	for (col = 0; col < ckdev->cols; col++) {
		for (row = 0; row < ckdev->rows; row++) {
			int pos = MATRIX_SCAN_CODE(row, col, ckdev->row_shift);
			const unsigned short *keycodes = idev->keycode;

			new_state = kb_state[col] & (1 << row);
			old_state = ckdev->old_kb_state[col] & (1 << row);
			if (new_state != old_state) {
				dev_dbg(ckdev->dev,
					"changed: [r%d c%d]: byte %02x\n",
					row, col, new_state);

				input_report_key(idev, keycodes[pos],
						 new_state);
			}
		}
		ckdev->old_kb_state[col] = kb_state[col];
	}
	input_sync(ckdev->idev);
}