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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u8 si1145_compress(u16 x)
{
	u32 exponent = 0;
	u32 significand = 0;
	u32 tmp = x;

	if (x == 0x0000)
		return 0x00;
	if (x == 0x0001)
		return 0x08;

	while (1) {
		tmp >>= 1;
		exponent += 1;
		if (tmp == 1)
			break;
	}

	if (exponent < 5) {
		significand = x << (4 - exponent);
		return (exponent << 4) | (significand & 0xF);
	}

	significand = x >> (exponent - 5);
	if (significand & 1) {
		significand += 2;
		if (significand & 0x0040) {
			exponent += 1;
			significand >>= 1;
		}
	}

	return (exponent << 4) | ((significand >> 1) & 0xF);
}