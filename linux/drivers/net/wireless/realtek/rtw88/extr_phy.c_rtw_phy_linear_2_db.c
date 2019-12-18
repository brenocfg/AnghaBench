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
typedef  scalar_t__ u64 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ FRAC_BITS ; 
 scalar_t__** db_invert_table ; 

__attribute__((used)) static u8 rtw_phy_linear_2_db(u64 linear)
{
	u8 i;
	u8 j;
	u32 dB;

	if (linear >= db_invert_table[11][7])
		return 96; /* maximum 96 dB */

	for (i = 0; i < 12; i++) {
		if (i <= 2 && (linear << FRAC_BITS) <= db_invert_table[i][7])
			break;
		else if (i > 2 && linear <= db_invert_table[i][7])
			break;
	}

	for (j = 0; j < 8; j++) {
		if (i <= 2 && (linear << FRAC_BITS) <= db_invert_table[i][j])
			break;
		else if (i > 2 && linear <= db_invert_table[i][j])
			break;
	}

	if (j == 0 && i == 0)
		goto end;

	if (j == 0) {
		if (i != 3) {
			if (db_invert_table[i][0] - linear >
			    linear - db_invert_table[i - 1][7]) {
				i = i - 1;
				j = 7;
			}
		} else {
			if (db_invert_table[3][0] - linear >
			    linear - db_invert_table[2][7]) {
				i = 2;
				j = 7;
			}
		}
	} else {
		if (db_invert_table[i][j] - linear >
		    linear - db_invert_table[i][j - 1]) {
			j = j - 1;
		}
	}
end:
	dB = (i << 3) + j + 1;

	return dB;
}