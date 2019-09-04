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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int MAX_ADDR_CELLS ; 

__attribute__((used)) static int sub_reg(u32 *reg, u32 *sub)
{
	int i, borrow = 0;

	for (i = MAX_ADDR_CELLS - 1; i >= 0; i--) {
		int prev_borrow = borrow;
		borrow = reg[i] < sub[i] + prev_borrow;
		reg[i] -= sub[i] + prev_borrow;
	}

	return !borrow;
}