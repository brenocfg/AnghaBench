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
struct pwc_dec23_private {unsigned int* table_dc00; unsigned int* table_d800; } ;

/* Variables and functions */

__attribute__((used)) static void fill_table_dc00_d800(struct pwc_dec23_private *pdec)
{
#define SCALEBITS 15
#define ONE_HALF  (1UL << (SCALEBITS - 1))
	int i;
	unsigned int offset1 = ONE_HALF;
	unsigned int offset2 = 0x0000;

	for (i=0; i<256; i++) {
		pdec->table_dc00[i] = offset1 & ~(ONE_HALF);
		pdec->table_d800[i] = offset2;

		offset1 += 0x7bc4;
		offset2 += 0x7bc4;
	}
}