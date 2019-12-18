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
typedef  int width ;
struct imstt_par {int /*<<< orphan*/  dc_regs; } ;
struct TYPE_4__ {int line_length; } ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct imstt_par* par; } ;
struct fb_copyarea {int sx; int sy; int dx; int dy; int height; int width; } ;
typedef  int line_pitch ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BLTCTL ; 
 int /*<<< orphan*/  CNT ; 
 int /*<<< orphan*/  DP_OCTL ; 
 int /*<<< orphan*/  DSA ; 
 int /*<<< orphan*/  S1SA ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  SSTATUS ; 
 int read_reg_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
imsttfb_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{
	struct imstt_par *par = info->par;
	__u32 Bpp, line_pitch, fb_offset_old, fb_offset_new, sp, dp_octl;
 	__u32 cnt, bltctl, sx, sy, dx, dy, height, width;

	Bpp = info->var.bits_per_pixel >> 3,

	sx = area->sx * Bpp;
	sy = area->sy;
	dx = area->dx * Bpp;
	dy = area->dy;
	height = area->height;
	height--;
	width = area->width * Bpp;
	width--;

	line_pitch = info->fix.line_length;
	bltctl = 0x05;
	sp = line_pitch << 16;
	cnt = height << 16;

	if (sy < dy) {
		sy += height;
		dy += height;
		sp |= -(line_pitch) & 0xffff;
		dp_octl = -(line_pitch) & 0xffff;
	} else {
		sp |= line_pitch;
		dp_octl = line_pitch;
	}
	if (sx < dx) {
		sx += width;
		dx += width;
		bltctl |= 0x80;
		cnt |= -(width) & 0xffff;
	} else {
		cnt |= width;
	}
	fb_offset_old = sy * line_pitch + sx;
	fb_offset_new = dy * line_pitch + dx;

	while(read_reg_le32(par->dc_regs, SSTATUS) & 0x80);
	write_reg_le32(par->dc_regs, S1SA, fb_offset_old);
	write_reg_le32(par->dc_regs, SP, sp);
	write_reg_le32(par->dc_regs, DSA, fb_offset_new);
	write_reg_le32(par->dc_regs, CNT, cnt);
	write_reg_le32(par->dc_regs, DP_OCTL, dp_octl);
	write_reg_le32(par->dc_regs, BLTCTL, bltctl);
	while(read_reg_le32(par->dc_regs, SSTATUS) & 0x80);
	while(read_reg_le32(par->dc_regs, SSTATUS) & 0x40);
}