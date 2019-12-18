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
typedef  unsigned char __u64 ;

/* Variables and functions */

__attribute__((used)) static int gf2k_get_bits(unsigned char *buf, int pos, int num, int shift)
{
	__u64 data = 0;
	int i;

	for (i = 0; i < num / 3 + 2; i++)
		data |= buf[pos / 3 + i] << (i * 3);
	data >>= pos % 3;
	data &= (1 << num) - 1;
	data <<= shift;

	return data;
}