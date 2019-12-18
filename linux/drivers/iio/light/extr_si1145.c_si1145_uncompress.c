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

__attribute__((used)) static u16 si1145_uncompress(u8 x)
{
	u16 result = 0;
	u8 exponent = 0;

	if (x < 8)
		return 0;

	exponent = (x & 0xf0) >> 4;
	result = 0x10 | (x & 0x0f);

	if (exponent >= 4)
		return result << (exponent - 4);
	return result >> (4 - exponent);
}