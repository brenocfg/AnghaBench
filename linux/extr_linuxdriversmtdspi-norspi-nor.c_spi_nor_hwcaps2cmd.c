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
 int EINVAL ; 

__attribute__((used)) static int spi_nor_hwcaps2cmd(u32 hwcaps, const int table[][2], size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (table[i][0] == (int)hwcaps)
			return table[i][1];

	return -EINVAL;
}