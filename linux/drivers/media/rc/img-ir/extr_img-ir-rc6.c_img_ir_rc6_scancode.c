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
struct img_ir_scancode_req {unsigned int scancode; unsigned int toggle; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 int IMG_IR_SCANCODE ; 
 int /*<<< orphan*/  RC_PROTO_RC6_0 ; 

__attribute__((used)) static int img_ir_rc6_scancode(int len, u64 raw, u64 enabled_protocols,
				struct img_ir_scancode_req *request)
{
	unsigned int addr, cmd, mode, trl1, trl2;

	/*
	 * Due to a side effect of the decoder handling the double length
	 * Trailer bit, the header information is a bit scrambled, and the
	 * raw data is shifted incorrectly.
	 * This workaround effectively recovers the header bits.
	 *
	 * The Header field should look like this:
	 *
	 * StartBit ModeBit2 ModeBit1 ModeBit0 TrailerBit
	 *
	 * But what we get is:
	 *
	 * ModeBit2 ModeBit1 ModeBit0 TrailerBit1 TrailerBit2
	 *
	 * The start bit is not important to recover the scancode.
	 */

	raw	>>= 27;

	trl1	= (raw >>  17)	& 0x01;
	trl2	= (raw >>  16)	& 0x01;

	mode	= (raw >>  18)	& 0x07;
	addr	= (raw >>   8)	& 0xff;
	cmd	=  raw		& 0xff;

	/*
	 * Due to the above explained irregularity the trailer bits cannot
	 * have the same value.
	 */
	if (trl1 == trl2)
		return -EINVAL;

	/* Only mode 0 supported for now */
	if (mode)
		return -EINVAL;

	request->protocol = RC_PROTO_RC6_0;
	request->scancode = addr << 8 | cmd;
	request->toggle	  = trl2;
	return IMG_IR_SCANCODE;
}