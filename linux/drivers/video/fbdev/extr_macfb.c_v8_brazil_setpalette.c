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
struct TYPE_3__ {unsigned int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; } ;
struct TYPE_4__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 int /*<<< orphan*/  nubus_writeb (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_2__* v8_brazil_cmap_regs ; 

__attribute__((used)) static int v8_brazil_setpalette(unsigned int regno, unsigned int red,
				unsigned int green, unsigned int blue,
				struct fb_info *info)
{
	unsigned int bpp = info->var.bits_per_pixel;
	unsigned long flags;

	local_irq_save(flags);

	/* On these chips, the CLUT register numbers are spread out
	 * across the register space.  Thus:
	 * In 8bpp, all regnos are valid.
	 * In 4bpp, the regnos are 0x0f, 0x1f, 0x2f, etc, etc
	 * In 2bpp, the regnos are 0x3f, 0x7f, 0xbf, 0xff
	 */
	regno = (regno << (8 - bpp)) | (0xFF >> bpp);
	nubus_writeb(regno, &v8_brazil_cmap_regs->addr);
	nop();

	/* send one color channel at a time */
	nubus_writeb(red, &v8_brazil_cmap_regs->lut);
	nop();
	nubus_writeb(green, &v8_brazil_cmap_regs->lut);
	nop();
	nubus_writeb(blue, &v8_brazil_cmap_regs->lut);

	local_irq_restore(flags);
	return 0;
}