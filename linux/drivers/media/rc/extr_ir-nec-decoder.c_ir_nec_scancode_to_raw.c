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
 int RC_PROTO_NEC32 ; 
 int RC_PROTO_NECX ; 

__attribute__((used)) static u32 ir_nec_scancode_to_raw(enum rc_proto protocol, u32 scancode)
{
	unsigned int addr, addr_inv, data, data_inv;

	data = scancode & 0xff;

	if (protocol == RC_PROTO_NEC32) {
		/* 32-bit NEC (used by Apple and TiVo remotes) */
		/* scan encoding: aaAAddDD */
		addr_inv   = (scancode >> 24) & 0xff;
		addr       = (scancode >> 16) & 0xff;
		data_inv   = (scancode >>  8) & 0xff;
	} else if (protocol == RC_PROTO_NECX) {
		/* Extended NEC */
		/* scan encoding AAaaDD */
		addr       = (scancode >> 16) & 0xff;
		addr_inv   = (scancode >>  8) & 0xff;
		data_inv   = data ^ 0xff;
	} else {
		/* Normal NEC */
		/* scan encoding: AADD */
		addr       = (scancode >>  8) & 0xff;
		addr_inv   = addr ^ 0xff;
		data_inv   = data ^ 0xff;
	}

	/* raw encoding: ddDDaaAA */
	return data_inv << 24 |
	       data     << 16 |
	       addr_inv <<  8 |
	       addr;
}