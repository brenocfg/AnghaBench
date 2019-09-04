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
struct bcm_kp {TYPE_1__* input_dev; int /*<<< orphan*/  n_cols; } ;
struct TYPE_2__ {unsigned short* keycode; } ;

/* Variables and functions */
 size_t MATRIX_SCAN_CODE (int,int,unsigned int) ; 
 unsigned int get_count_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_kp_get_keycode(struct bcm_kp *kp, int row, int col)
{
	unsigned int row_shift = get_count_order(kp->n_cols);
	unsigned short *keymap = kp->input_dev->keycode;

	return keymap[MATRIX_SCAN_CODE(row, col, row_shift)];
}