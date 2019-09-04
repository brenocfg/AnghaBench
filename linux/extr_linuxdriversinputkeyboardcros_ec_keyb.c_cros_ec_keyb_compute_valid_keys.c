#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cros_ec_keyb {int row_shift; int cols; int rows; int* valid_keys; int /*<<< orphan*/  dev; TYPE_1__* idev; } ;
struct TYPE_2__ {unsigned short* keycode; int keycodesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned short KEY_BATTERY ; 
 size_t MATRIX_SCAN_CODE (int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void cros_ec_keyb_compute_valid_keys(struct cros_ec_keyb *ckdev)
{
	int row, col;
	int row_shift = ckdev->row_shift;
	unsigned short *keymap = ckdev->idev->keycode;
	unsigned short code;

	BUG_ON(ckdev->idev->keycodesize != sizeof(*keymap));

	for (col = 0; col < ckdev->cols; col++) {
		for (row = 0; row < ckdev->rows; row++) {
			code = keymap[MATRIX_SCAN_CODE(row, col, row_shift)];
			if (code && (code != KEY_BATTERY))
				ckdev->valid_keys[col] |= 1 << row;
		}
		dev_dbg(ckdev->dev, "valid_keys[%02d] = 0x%02x\n",
			col, ckdev->valid_keys[col]);
	}
}