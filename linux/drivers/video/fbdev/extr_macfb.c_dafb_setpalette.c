#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* red; int* green; int* blue; } ;
struct fb_info {TYPE_1__ cmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 TYPE_2__* dafb_cmap_regs ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 int /*<<< orphan*/  nubus_writeb (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nubus_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dafb_setpalette(unsigned int regno, unsigned int red,
			   unsigned int green, unsigned int blue,
			   struct fb_info *info)
{
	static int lastreg = -2;
	unsigned long flags;

	local_irq_save(flags);

	/*
	 * fbdev will set an entire colourmap, but X won't.  Hopefully
	 * this should accommodate both of them
	 */
	if (regno != lastreg + 1) {
		int i;

		/* Stab in the dark trying to reset the CLUT pointer */
		nubus_writel(0, &dafb_cmap_regs->reset);
		nop();

		/* Loop until we get to the register we want */
		for (i = 0; i < regno; i++) {
			nubus_writeb(info->cmap.red[i] >> 8,
				     &dafb_cmap_regs->lut);
			nop();
			nubus_writeb(info->cmap.green[i] >> 8,
				     &dafb_cmap_regs->lut);
			nop();
			nubus_writeb(info->cmap.blue[i] >> 8,
				     &dafb_cmap_regs->lut);
			nop();
		}
	}

	nubus_writeb(red, &dafb_cmap_regs->lut);
	nop();
	nubus_writeb(green, &dafb_cmap_regs->lut);
	nop();
	nubus_writeb(blue, &dafb_cmap_regs->lut);

	local_irq_restore(flags);
	lastreg = regno;
	return 0;
}