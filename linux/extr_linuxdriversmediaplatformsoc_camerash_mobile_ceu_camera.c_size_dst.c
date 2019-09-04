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

__attribute__((used)) static unsigned int size_dst(unsigned int src, unsigned int scale)
{
	unsigned int mant_pre = scale >> 12;
	if (!src || !scale)
		return src;
	return ((mant_pre + 2 * (src - 1)) / (2 * mant_pre) - 1) *
		mant_pre * 4096 / scale + 1;
}