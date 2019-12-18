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
typedef  scalar_t__ u8 ;
typedef  int u16 ;

/* Variables and functions */

u16
nvbios_findstr(const u8 *data, int size, const char *str, int len)
{
	int i, j;

	for (i = 0; i <= (size - len); i++) {
		for (j = 0; j < len; j++)
			if ((char)data[i + j] != str[j])
				break;
		if (j == len)
			return i;
	}

	return 0;
}