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
struct slookup {scalar_t__ reg_value; int value; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static s32 table_lookup(const struct slookup *table,
			int table_size, u32 reg_value)
{
	s32 value;
	int imin = 0;
	int imax = table_size - 1;
	int i;
	s32 reg_diff;

	/* Assumes Table[0].RegValue > Table[imax].RegValue */
	if (reg_value >= table[0].reg_value) {
		value = table[0].value;
	} else if (reg_value <= table[imax].reg_value) {
		value = table[imax].value;
	} else {
		while ((imax - imin) > 1) {
			i = (imax + imin) / 2;
			if ((table[imin].reg_value >= reg_value) &&
			    (reg_value >= table[i].reg_value))
				imax = i;
			else
				imin = i;
		}

		reg_diff = table[imax].reg_value - table[imin].reg_value;
		value = table[imin].value;
		if (reg_diff != 0)
			value += ((s32)(reg_value - table[imin].reg_value) *
				  (s32)(table[imax].value
					- table[imin].value))
					/ (reg_diff);
	}

	return value;
}