#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned short base; int mode; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
#define  IMM_NIBBLE 129 
#define  IMM_PS2 128 
 int /*<<< orphan*/  imm_fail (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned short,unsigned char) ; 

__attribute__((used)) static int imm_negotiate(imm_struct * tmp)
{
	/*
	 * The following is supposedly the IEEE 1284-1994 negotiate
	 * sequence. I have yet to obtain a copy of the above standard
	 * so this is a bit of a guess...
	 *
	 * A fair chunk of this is based on the Linux parport implementation
	 * of IEEE 1284.
	 *
	 * Return 0 if data available
	 *        1 if no data available
	 */

	unsigned short base = tmp->base;
	unsigned char a, mode;

	switch (tmp->mode) {
	case IMM_NIBBLE:
		mode = 0x00;
		break;
	case IMM_PS2:
		mode = 0x01;
		break;
	default:
		return 0;
	}

	w_ctr(base, 0x04);
	udelay(5);
	w_dtr(base, mode);
	udelay(100);
	w_ctr(base, 0x06);
	udelay(5);
	a = (r_str(base) & 0x20) ? 0 : 1;
	udelay(5);
	w_ctr(base, 0x07);
	udelay(5);
	w_ctr(base, 0x06);

	if (a) {
		printk
		    ("IMM: IEEE1284 negotiate indicates no data available.\n");
		imm_fail(tmp, DID_ERROR);
	}
	return a;
}