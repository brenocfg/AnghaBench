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
typedef  unsigned char u8 ;

/* Variables and functions */
 int BIT (int) ; 

int rtw_get_bit_value_from_ieee_value(u8 val)
{
	unsigned char dot11_rate_table[] = {2, 4, 11, 22, 12, 18, 24, 36, 48, 72, 96, 108, 0}; /*  last element must be zero!! */
	int i = 0;

	while (dot11_rate_table[i] != 0) {
		if (dot11_rate_table[i] == val)
			return BIT(i);
		i++;
	}
	return 0;
}