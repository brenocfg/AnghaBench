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

__attribute__((used)) static int ddr3_cs_size(unsigned i, bool dct_width)
{
	unsigned shift = 0;
	int cs_size = 0;

	if (i == 0 || i == 3 || i == 4)
		cs_size = -1;
	else if (i <= 2)
		shift = i;
	else if (i == 12)
		shift = 7;
	else if (!(i & 0x1))
		shift = i >> 1;
	else
		shift = (i + 1) >> 1;

	if (cs_size != -1)
		cs_size = (128 * (1 << !!dct_width)) << shift;

	return cs_size;
}