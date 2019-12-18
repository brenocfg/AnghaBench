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
 unsigned char EOC ; 
 unsigned char HNib ; 
 scalar_t__ PAR_DATA ; 
 unsigned char WrAddr ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static inline void
write_reg_high(short port, unsigned char reg, unsigned char value)
{
	unsigned char outval = EOC | HNib | reg;

	outb(outval, port + PAR_DATA);
	outval &= WrAddr | HNib | 0x0f;
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);	/* Double write for PS/2. */

	outval = WrAddr | HNib | value;
	outb(outval, port + PAR_DATA);
	outval &= HNib | 0x0f;		/* HNib | value */
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);

	outb(EOC | HNib | outval, port + PAR_DATA);
}