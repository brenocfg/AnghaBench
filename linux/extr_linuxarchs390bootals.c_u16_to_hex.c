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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void u16_to_hex(char *str, u16 val)
{
	int i, num;

	for (i = 1; i <= 4; i++) {
		num = (val >> (16 - 4 * i)) & 0xf;
		if (num >= 10)
			num += 7;
		*str++ = '0' + num;
	}
	*str = '\0';
}