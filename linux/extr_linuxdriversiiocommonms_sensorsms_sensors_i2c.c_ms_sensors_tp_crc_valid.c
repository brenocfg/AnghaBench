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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static bool ms_sensors_tp_crc_valid(u16 *prom, u8 len)
{
	unsigned int cnt, n_bit;
	u16 n_rem = 0x0000, crc_read = prom[0], crc = (*prom & 0xF000) >> 12;

	prom[len - 1] = 0;
	prom[0] &= 0x0FFF;      /* Clear the CRC computation part */

	for (cnt = 0; cnt < len * 2; cnt++) {
		if (cnt % 2 == 1)
			n_rem ^= prom[cnt >> 1] & 0x00FF;
		else
			n_rem ^= prom[cnt >> 1] >> 8;

		for (n_bit = 8; n_bit > 0; n_bit--) {
			if (n_rem & 0x8000)
				n_rem = (n_rem << 1) ^ 0x3000;
			else
				n_rem <<= 1;
		}
	}
	n_rem >>= 12;
	prom[0] = crc_read;

	return n_rem == crc;
}