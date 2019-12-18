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
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
#define  RC_PROTO_NEC32 131 
#define  RC_PROTO_NECX 130 
#define  RC_PROTO_RC6_6A_32 129 
#define  RC_PROTO_RC6_MCE 128 

bool rc_validate_scancode(enum rc_proto proto, u32 scancode)
{
	switch (proto) {
	/*
	 * NECX has a 16-bit address; if the lower 8 bits match the upper
	 * 8 bits inverted, then the address would match regular nec.
	 */
	case RC_PROTO_NECX:
		if ((((scancode >> 16) ^ ~(scancode >> 8)) & 0xff) == 0)
			return false;
		break;
	/*
	 * NEC32 has a 16 bit address and 16 bit command. If the lower 8 bits
	 * of the command match the upper 8 bits inverted, then it would
	 * be either NEC or NECX.
	 */
	case RC_PROTO_NEC32:
		if ((((scancode >> 8) ^ ~scancode) & 0xff) == 0)
			return false;
		break;
	/*
	 * If the customer code (top 32-bit) is 0x800f, it is MCE else it
	 * is regular mode-6a 32 bit
	 */
	case RC_PROTO_RC6_MCE:
		if ((scancode & 0xffff0000) != 0x800f0000)
			return false;
		break;
	case RC_PROTO_RC6_6A_32:
		if ((scancode & 0xffff0000) == 0x800f0000)
			return false;
		break;
	default:
		break;
	}

	return true;
}