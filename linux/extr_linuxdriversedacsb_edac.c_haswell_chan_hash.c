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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static int haswell_chan_hash(int idx, u64 addr)
{
	int i;

	/*
	 * XOR even bits from 12:26 to bit0 of idx,
	 *     odd bits from 13:27 to bit1
	 */
	for (i = 12; i < 28; i += 2)
		idx ^= (addr >> i) & 3;

	return idx;
}