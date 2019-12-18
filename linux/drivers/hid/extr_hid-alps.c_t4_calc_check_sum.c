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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 t4_calc_check_sum(u8 *buffer,
		unsigned long offset, unsigned long length)
{
	u16 sum1 = 0xFF, sum2 = 0xFF;
	unsigned long i = 0;

	if (offset + length >= 50)
		return 0;

	while (length > 0) {
		u32 tlen = length > 20 ? 20 : length;

		length -= tlen;

		do {
			sum1 += buffer[offset + i];
			sum2 += sum1;
			i++;
		} while (--tlen > 0);

		sum1 = (sum1 & 0xFF) + (sum1 >> 8);
		sum2 = (sum2 & 0xFF) + (sum2 >> 8);
	}

	sum1 = (sum1 & 0xFF) + (sum1 >> 8);
	sum2 = (sum2 & 0xFF) + (sum2 >> 8);

	return(sum2 << 8 | sum1);
}