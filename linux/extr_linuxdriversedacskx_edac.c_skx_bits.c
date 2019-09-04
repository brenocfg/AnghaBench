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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static int skx_bits(u64 addr, int nbits, u8 *bits)
{
	int i, res = 0;

	for (i = 0; i < nbits; i++)
		res |= ((addr >> bits[i]) & 1) << i;
	return res;
}