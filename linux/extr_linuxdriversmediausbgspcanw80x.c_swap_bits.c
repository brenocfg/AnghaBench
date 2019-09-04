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

__attribute__((used)) static int swap_bits(int v)
{
	int r, i;

	r = 0;
	for (i = 0; i < 8; i++) {
		r <<= 1;
		if (v & 1)
			r++;
		v >>= 1;
	}
	return r;
}