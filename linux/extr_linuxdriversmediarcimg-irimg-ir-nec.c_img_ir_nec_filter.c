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
typedef  int u64 ;
struct rc_scancode_filter {int data; int mask; } ;
struct img_ir_filter {unsigned int data; unsigned int mask; } ;

/* Variables and functions */
 int RC_PROTO_BIT_NEC ; 
 int RC_PROTO_BIT_NEC32 ; 
 int RC_PROTO_BIT_NECX ; 
 unsigned int bitrev8 (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int img_ir_nec_filter(const struct rc_scancode_filter *in,
			     struct img_ir_filter *out, u64 protocols)
{
	unsigned int addr, addr_inv, data, data_inv;
	unsigned int addr_m, addr_inv_m, data_m, data_inv_m;

	data       = in->data & 0xff;
	data_m     = in->mask & 0xff;

	protocols &= RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32;

	/*
	 * If only one bit is set, we were requested to do an exact
	 * protocol. This should be the case for wakeup filters; for
	 * normal filters, guess the protocol from the scancode.
	 */
	if (!is_power_of_2(protocols)) {
		if ((in->data | in->mask) & 0xff000000)
			protocols = RC_PROTO_BIT_NEC32;
		else if ((in->data | in->mask) & 0x00ff0000)
			protocols = RC_PROTO_BIT_NECX;
		else
			protocols = RC_PROTO_BIT_NEC;
	}

	if (protocols == RC_PROTO_BIT_NEC32) {
		/* 32-bit NEC (used by Apple and TiVo remotes) */
		/* scan encoding: as transmitted, MSBit = first received bit */
		addr       = bitrev8(in->data >> 24);
		addr_m     = bitrev8(in->mask >> 24);
		addr_inv   = bitrev8(in->data >> 16);
		addr_inv_m = bitrev8(in->mask >> 16);
		data       = bitrev8(in->data >>  8);
		data_m     = bitrev8(in->mask >>  8);
		data_inv   = bitrev8(in->data >>  0);
		data_inv_m = bitrev8(in->mask >>  0);
	} else if (protocols == RC_PROTO_BIT_NECX) {
		/* Extended NEC */
		/* scan encoding AAaaDD */
		addr       = (in->data >> 16) & 0xff;
		addr_m     = (in->mask >> 16) & 0xff;
		addr_inv   = (in->data >>  8) & 0xff;
		addr_inv_m = (in->mask >>  8) & 0xff;
		data_inv   = data ^ 0xff;
		data_inv_m = data_m;
	} else {
		/* Normal NEC */
		/* scan encoding: AADD */
		addr       = (in->data >>  8) & 0xff;
		addr_m     = (in->mask >>  8) & 0xff;
		addr_inv   = addr ^ 0xff;
		addr_inv_m = addr_m;
		data_inv   = data ^ 0xff;
		data_inv_m = data_m;
	}

	/* raw encoding: ddDDaaAA */
	out->data = data_inv << 24 |
		    data     << 16 |
		    addr_inv <<  8 |
		    addr;
	out->mask = data_inv_m << 24 |
		    data_m     << 16 |
		    addr_inv_m <<  8 |
		    addr_m;
	return 0;
}