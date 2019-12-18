#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  regs; void* dcdcheck; int /*<<< orphan*/ * irqs; } ;
struct TYPE_5__ {int /*<<< orphan*/  regs; void* dcdcheck; int /*<<< orphan*/ * irqs; } ;
struct z8530_dev {TYPE_1__ chanB; TYPE_2__ chanA; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 void* DCD ; 
 int ENODEV ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R12 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int Tx_BUF_EMP ; 
 int /*<<< orphan*/  Z85230 ; 
 int /*<<< orphan*/  Z8530 ; 
 int /*<<< orphan*/  Z85C30 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int read_zsreg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_init ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_zsreg (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z8530_nop ; 

__attribute__((used)) static inline int do_z8530_init(struct z8530_dev *dev)
{
	/* NOP the interrupt handlers first - we might get a
	   floating IRQ transition when we reset the chip */
	dev->chanA.irqs=&z8530_nop;
	dev->chanB.irqs=&z8530_nop;
	dev->chanA.dcdcheck=DCD;
	dev->chanB.dcdcheck=DCD;

	/* Reset the chip */
	write_zsreg(&dev->chanA, R9, 0xC0);
	udelay(200);
	/* Now check its valid */
	write_zsreg(&dev->chanA, R12, 0xAA);
	if(read_zsreg(&dev->chanA, R12)!=0xAA)
		return -ENODEV;
	write_zsreg(&dev->chanA, R12, 0x55);
	if(read_zsreg(&dev->chanA, R12)!=0x55)
		return -ENODEV;
		
	dev->type=Z8530;
	
	/*
	 *	See the application note.
	 */
	 
	write_zsreg(&dev->chanA, R15, 0x01);
	
	/*
	 *	If we can set the low bit of R15 then
	 *	the chip is enhanced.
	 */
	 
	if(read_zsreg(&dev->chanA, R15)==0x01)
	{
		/* This C30 versus 230 detect is from Klaus Kudielka's dmascc */
		/* Put a char in the fifo */
		write_zsreg(&dev->chanA, R8, 0);
		if(read_zsreg(&dev->chanA, R0)&Tx_BUF_EMP)
			dev->type = Z85230;	/* Has a FIFO */
		else
			dev->type = Z85C30;	/* Z85C30, 1 byte FIFO */
	}
		
	/*
	 *	The code assumes R7' and friends are
	 *	off. Use write_zsext() for these and keep
	 *	this bit clear.
	 */
	 
	write_zsreg(&dev->chanA, R15, 0);
		
	/*
	 *	At this point it looks like the chip is behaving
	 */
	 
	memcpy(dev->chanA.regs, reg_init, 16);
	memcpy(dev->chanB.regs, reg_init ,16);
	
	return 0;
}