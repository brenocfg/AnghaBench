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

/* Variables and functions */

__attribute__((used)) static int nrbits(unsigned int val, int bitcount)
{
	int i, total = 0;

	for (i = 0; (i < bitcount); i++)
		total += (((0x1 << i) & val) ? 1 : 0);
	return total;
}