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
typedef  int u64 ;

/* Variables and functions */
 int FRAC_BITS ; 
 int** db_invert_table ; 

__attribute__((used)) static u64 rtw_phy_db_2_linear(u8 power_db)
{
	u8 i, j;
	u64 linear;

	if (power_db > 96)
		power_db = 96;
	else if (power_db < 1)
		return 1;

	/* 1dB ~ 96dB */
	i = (power_db - 1) >> 3;
	j = (power_db - 1) - (i << 3);

	linear = db_invert_table[i][j];
	linear = i > 2 ? linear << FRAC_BITS : linear;

	return linear;
}