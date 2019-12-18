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
typedef  int u32 ;
typedef  int sint ;

/* Variables and functions */
 int CRC32_POLY_BE ; 
 int bcrc32initialized ; 
 scalar_t__ crc32_reverseBit (scalar_t__) ; 
 int /*<<< orphan*/ * crc32_table ; 

__attribute__((used)) static void crc32_init(void)
{
	sint i, j;
	u32 c;
	u8 *p = (u8 *)&c, *p1;
	u8 k;

	if (bcrc32initialized == 1)
		return;

	for (i = 0; i < 256; ++i) {
		k = crc32_reverseBit((u8)i);
		for (c = ((u32)k) << 24, j = 8; j > 0; --j)
			c = c & 0x80000000 ? (c << 1) ^ CRC32_POLY_BE : (c << 1);
		p1 = (u8 *)&crc32_table[i];
		p1[0] = crc32_reverseBit(p[3]);
		p1[1] = crc32_reverseBit(p[2]);
		p1[2] = crc32_reverseBit(p[1]);
		p1[3] = crc32_reverseBit(p[0]);
	}
	bcrc32initialized = 1;
}