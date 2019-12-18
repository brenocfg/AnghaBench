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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u8 esas2r_calc_byte_xor_cksum(u8 *addr, u32 len, u8 seed)
{
	u32 cksum = seed;
	u8 *p = (u8 *)&cksum;

	while (len) {
		if (((uintptr_t)addr & 3) == 0)
			break;

		cksum = cksum ^ *addr;
		addr++;
		len--;
	}
	while (len >= sizeof(u32)) {
		cksum = cksum ^ *(u32 *)addr;
		addr += 4;
		len -= 4;
	}
	while (len--) {
		cksum = cksum ^ *addr;
		addr++;
	}
	return p[0] ^ p[1] ^ p[2] ^ p[3];
}