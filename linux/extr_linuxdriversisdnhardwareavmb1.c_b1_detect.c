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
typedef  enum avmcardtype { ____Placeholder_avmcardtype } avmcardtype ;

/* Variables and functions */
 scalar_t__ B1_INSTAT ; 
 scalar_t__ B1_OUTSTAT ; 
 int /*<<< orphan*/  B1_STAT1 (int) ; 
 int avm_m1 ; 
 int b1_get_test_bit (unsigned int,int) ; 
 int b1_rd_reg (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1_set_test_bit (unsigned int,int,int) ; 
 int /*<<< orphan*/  b1outp (unsigned int,scalar_t__,int) ; 
 int inb (scalar_t__) ; 

int b1_detect(unsigned int base, enum avmcardtype cardtype)
{
	int onoff, i;

	/*
	 * Statusregister 0000 00xx
	 */
	if ((inb(base + B1_INSTAT) & 0xfc)
	    || (inb(base + B1_OUTSTAT) & 0xfc))
		return 1;
	/*
	 * Statusregister 0000 001x
	 */
	b1outp(base, B1_INSTAT, 0x2);	/* enable irq */
	/* b1outp(base, B1_OUTSTAT, 0x2); */
	if ((inb(base + B1_INSTAT) & 0xfe) != 0x2
	    /* || (inb(base + B1_OUTSTAT) & 0xfe) != 0x2 */)
		return 2;
	/*
	 * Statusregister 0000 000x
	 */
	b1outp(base, B1_INSTAT, 0x0);	/* disable irq */
	b1outp(base, B1_OUTSTAT, 0x0);
	if ((inb(base + B1_INSTAT) & 0xfe)
	    || (inb(base + B1_OUTSTAT) & 0xfe))
		return 3;

	for (onoff = !0, i = 0; i < 10; i++) {
		b1_set_test_bit(base, cardtype, onoff);
		if (b1_get_test_bit(base, cardtype) != onoff)
			return 4;
		onoff = !onoff;
	}

	if (cardtype == avm_m1)
		return 0;

	if ((b1_rd_reg(base, B1_STAT1(cardtype)) & 0x0f) != 0x01)
		return 5;

	return 0;
}