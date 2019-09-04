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

__attribute__((used)) static unsigned int qat_uclo_calc_checksum(unsigned int reg, int ch)
{
	int i;
	unsigned int topbit = 1 << 0xF;
	unsigned int inbyte = (unsigned int)((reg >> 0x18) ^ ch);

	reg ^= inbyte << 0x8;
	for (i = 0; i < 0x8; i++) {
		if (reg & topbit)
			reg = (reg << 1) ^ 0x1021;
		else
			reg <<= 1;
	}
	return reg & 0xFFFF;
}