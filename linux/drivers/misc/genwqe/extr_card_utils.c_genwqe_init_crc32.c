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
typedef  int u32 ;

/* Variables and functions */
 int CRC32_POLYNOMIAL ; 
 int* crc32_tab ; 

void genwqe_init_crc32(void)
{
	int i, j;
	u32 crc;

	for (i = 0;  i < 256;  i++) {
		crc = i << 24;
		for (j = 0;  j < 8;  j++) {
			if (crc & 0x80000000)
				crc = (crc << 1) ^ CRC32_POLYNOMIAL;
			else
				crc = (crc << 1);
		}
		crc32_tab[i] = crc;
	}
}