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
typedef  int u16 ;
struct pmic8xxx_kp {int num_rows; int num_cols; int /*<<< orphan*/  input; int /*<<< orphan*/ * keycodes; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  PM8XXX_ROW_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pmic8xxx_kp_scan_matrix(struct pmic8xxx_kp *kp, u16 *new_state,
					 u16 *old_state)
{
	int row, col, code;

	for (row = 0; row < kp->num_rows; row++) {
		int bits_changed = new_state[row] ^ old_state[row];

		if (!bits_changed)
			continue;

		for (col = 0; col < kp->num_cols; col++) {
			if (!(bits_changed & (1 << col)))
				continue;

			dev_dbg(kp->dev, "key [%d:%d] %s\n", row, col,
					!(new_state[row] & (1 << col)) ?
					"pressed" : "released");

			code = MATRIX_SCAN_CODE(row, col, PM8XXX_ROW_SHIFT);

			input_event(kp->input, EV_MSC, MSC_SCAN, code);
			input_report_key(kp->input,
					kp->keycodes[code],
					!(new_state[row] & (1 << col)));

			input_sync(kp->input);
		}
	}
}