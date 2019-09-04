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

void cx231xx_swab(u16 *from, u16 *to, u16 len)
{
	u16 i;

	if (len <= 0)
		return;

	for (i = 0; i < len / 2; i++)
		to[i] = (from[i] << 8) | (from[i] >> 8);
}