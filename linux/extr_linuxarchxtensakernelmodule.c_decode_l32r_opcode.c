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

__attribute__((used)) static int
decode_l32r_opcode (unsigned char *location)
{
#ifdef __XTENSA_EB__
	return (location[0] & 0xf0) == 0x10;
#endif
#ifdef __XTENSA_EL__
	return (location[0] & 0xf) == 0x1;
#endif
}