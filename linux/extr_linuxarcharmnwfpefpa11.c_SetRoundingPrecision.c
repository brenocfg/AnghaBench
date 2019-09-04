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
typedef  int int8 ;

/* Variables and functions */

int8 SetRoundingPrecision(const unsigned int opcode)
{
#ifdef CONFIG_FPE_NWFPE_XP
	switch (opcode & MASK_ROUNDING_PRECISION) {
	case ROUND_SINGLE:
		return 32;

	case ROUND_DOUBLE:
		return 64;

	case ROUND_EXTENDED:
		return 80;

	default:
		return 80;
	}
#endif
	return 80;
}