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

__attribute__((used)) static int pack_mb88341(int addr, int val, int *bitstring)
{
	/*
	 * Fujitsu MB 88341
	 * Note that address bits are reversed.  Thanks to
	 * Ingo Keen for noticing this.
	 *
	 * Note also that the 88341 expects address values from
	 * 1-12, whereas we use channel numbers 0-11.  The NI
	 * docs use 1-12, also, so be careful here.
	 */
	addr++;
	*bitstring = ((addr & 0x1) << 11) |
	    ((addr & 0x2) << 9) |
	    ((addr & 0x4) << 7) | ((addr & 0x8) << 5) | (val & 0xff);
	return 12;
}