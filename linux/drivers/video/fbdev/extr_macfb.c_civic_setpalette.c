#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  status2; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 TYPE_1__* civic_cmap_regs ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 void* nubus_readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nubus_writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int civic_setpalette(unsigned int regno, unsigned int red,
			    unsigned int green, unsigned int blue,
			    struct fb_info *info)
{
	unsigned long flags;
	int clut_status;
	
	local_irq_save(flags);

	/* Set the register address */
	nubus_writeb(regno, &civic_cmap_regs->addr);
	nop();

	/*
	 * Grab a status word and do some checking;
	 * Then finally write the clut!
	 */
	clut_status =  nubus_readb(&civic_cmap_regs->status2);

	if ((clut_status & 0x0008) == 0)
	{
#if 0
		if ((clut_status & 0x000D) != 0)
		{
			nubus_writeb(0x00, &civic_cmap_regs->lut);
			nop();
			nubus_writeb(0x00, &civic_cmap_regs->lut);
			nop();
		}
#endif

		nubus_writeb(red, &civic_cmap_regs->lut);
		nop();
		nubus_writeb(green, &civic_cmap_regs->lut);
		nop();
		nubus_writeb(blue, &civic_cmap_regs->lut);
		nop();
		nubus_writeb(0x00, &civic_cmap_regs->lut);
	}
	else
	{
		unsigned char junk;

		junk = nubus_readb(&civic_cmap_regs->lut);
		nop();
		junk = nubus_readb(&civic_cmap_regs->lut);
		nop();
		junk = nubus_readb(&civic_cmap_regs->lut);
		nop();
		junk = nubus_readb(&civic_cmap_regs->lut);
		nop();

		if ((clut_status & 0x000D) != 0)
		{
			nubus_writeb(0x00, &civic_cmap_regs->lut);
			nop();
			nubus_writeb(0x00, &civic_cmap_regs->lut);
			nop();
		}

		nubus_writeb(red, &civic_cmap_regs->lut);
		nop();
		nubus_writeb(green, &civic_cmap_regs->lut);
		nop();
		nubus_writeb(blue, &civic_cmap_regs->lut);
		nop();
		nubus_writeb(junk, &civic_cmap_regs->lut);
	}

	local_irq_restore(flags);
	return 0;
}