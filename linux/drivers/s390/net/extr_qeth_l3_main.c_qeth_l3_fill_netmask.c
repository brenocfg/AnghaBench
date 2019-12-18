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
typedef  int len ;

/* Variables and functions */

__attribute__((used)) static void qeth_l3_fill_netmask(u8 *netmask, unsigned int len)
{
	int i, j;
	for (i = 0; i < 16; i++) {
		j = (len) - (i * 8);
		if (j >= 8)
			netmask[i] = 0xff;
		else if (j > 0)
			netmask[i] = (u8)(0xFF00 >> j);
		else
			netmask[i] = 0;
	}
}