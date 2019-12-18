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
 int /*<<< orphan*/  Ctrl_HNibRead ; 
 int /*<<< orphan*/  Ctrl_LNibRead ; 
 scalar_t__ PAR_CONTROL ; 
 scalar_t__ PAR_STATUS ; 
 int inbyte (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline unsigned char read_byte_mode2(short ioaddr)
{
	unsigned char low_nib;

	outb(Ctrl_LNibRead, ioaddr + PAR_CONTROL);
	inbyte(ioaddr + PAR_STATUS);
	low_nib = (inbyte(ioaddr + PAR_STATUS) >> 3) & 0x0f;
	outb(Ctrl_HNibRead, ioaddr + PAR_CONTROL);
	inbyte(ioaddr + PAR_STATUS);	/* Settling time delay -- needed!  */
	return low_nib | ((inbyte(ioaddr + PAR_STATUS) << 1) & 0xf0);
}