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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void jz_nand_correct_data(uint8_t *dat, int index, int mask)
{
	int offset = index & 0x7;
	uint16_t data;

	index += (index >> 3);

	data = dat[index];
	data |= dat[index+1] << 8;

	mask ^= (data >> offset) & 0x1ff;
	data &= ~(0x1ff << offset);
	data |= (mask << offset);

	dat[index] = data & 0xff;
	dat[index+1] = (data >> 8) & 0xff;
}