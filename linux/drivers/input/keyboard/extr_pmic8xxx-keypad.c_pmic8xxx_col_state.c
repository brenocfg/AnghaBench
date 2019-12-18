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
struct pmic8xxx_kp {int num_cols; } ;

/* Variables and functions */

__attribute__((used)) static u8 pmic8xxx_col_state(struct pmic8xxx_kp *kp, u8 col)
{
	/* all keys pressed on that particular row? */
	if (col == 0x00)
		return 1 << kp->num_cols;
	else
		return col & ((1 << kp->num_cols) - 1);
}