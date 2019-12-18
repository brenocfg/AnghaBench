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
struct TYPE_2__ {unsigned int len; } ;
struct fb_info {TYPE_1__ cmap; } ;

/* Variables and functions */
 scalar_t__ fb_regs ; 
 int in_be16 (scalar_t__) ; 
 int /*<<< orphan*/  out_be16 (scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hpfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			  unsigned blue, unsigned transp,
			  struct fb_info *info)
{
	/* use MSBs */
	unsigned char _red  =red>>8;
	unsigned char _green=green>>8;
	unsigned char _blue =blue>>8;
	unsigned char _regno=regno;

	/*
	 *  Set a single color register. The values supplied are
	 *  already rounded down to the hardware's capabilities
	 *  (according to the entries in the `var' structure). Return
	 *  != 0 for invalid regno.
	 */

	if (regno >= info->cmap.len)
		return 1;
	
	while (in_be16(fb_regs + 0x6002) & 0x4) udelay(1);

	out_be16(fb_regs + 0x60ba, 0xff);

	out_be16(fb_regs + 0x60b2, _red);
	out_be16(fb_regs + 0x60b4, _green);
	out_be16(fb_regs + 0x60b6, _blue);
	out_be16(fb_regs + 0x60b8, ~_regno);
	out_be16(fb_regs + 0x60f0, 0xff);

	udelay(100);

	while (in_be16(fb_regs + 0x6002) & 0x4) udelay(1);
	out_be16(fb_regs + 0x60b2, 0);
	out_be16(fb_regs + 0x60b4, 0);
	out_be16(fb_regs + 0x60b6, 0);
	out_be16(fb_regs + 0x60b8, 0);

	return 0;
}