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
typedef  int u16 ;
struct twl4030_keypad {int n_cols; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 twl4030_col_xlate(struct twl4030_keypad *kp, u8 col)
{
	/*
	 * If all bits in a row are active for all columns then
	 * we have that row line connected to gnd. Mark this
	 * key on as if it was on matrix position n_cols (i.e.
	 * one higher than the size of the matrix).
	 */
	if (col == 0xFF)
		return 1 << kp->n_cols;
	else
		return col & ((1 << kp->n_cols) - 1);
}