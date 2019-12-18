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
struct jet_cmap_regs {int /*<<< orphan*/  lut; int /*<<< orphan*/  addr; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 int /*<<< orphan*/  nubus_writeb (unsigned int,int /*<<< orphan*/ *) ; 
 struct jet_cmap_regs* slot_addr ; 

__attribute__((used)) static int jet_setpalette(unsigned int regno, unsigned int red,
			  unsigned int green, unsigned int blue,
			  struct fb_info *info)
{
	struct jet_cmap_regs *cmap_regs = slot_addr;
	unsigned long flags;

	local_irq_save(flags);

	nubus_writeb(regno, &cmap_regs->addr);
	nop();
	nubus_writeb(red, &cmap_regs->lut);
	nop();
	nubus_writeb(green, &cmap_regs->lut);
	nop();
	nubus_writeb(blue, &cmap_regs->lut);

	local_irq_restore(flags);
	return 0;
}