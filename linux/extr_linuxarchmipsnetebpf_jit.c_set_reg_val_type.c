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
typedef  unsigned long long u64 ;
typedef  enum reg_val_type { ____Placeholder_reg_val_type } reg_val_type ;

/* Variables and functions */

__attribute__((used)) static void set_reg_val_type(u64 *rvt, int reg, enum reg_val_type type)
{
	*rvt &= ~(7ull << (reg * 3));
	*rvt |= ((u64)type << (reg * 3));
}