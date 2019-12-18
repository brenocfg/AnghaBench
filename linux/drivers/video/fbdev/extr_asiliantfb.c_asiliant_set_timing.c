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
struct TYPE_2__ {int xres; int right_margin; int hsync_len; int left_margin; unsigned int yres; unsigned int lower_margin; unsigned int vsync_len; unsigned int upper_margin; int xres_virtual; int bits_per_pixel; int pixclock; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 scalar_t__ mmio_base ; 
 int /*<<< orphan*/  write_cr (int,int) ; 
 int /*<<< orphan*/  write_fr (int,int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void asiliant_set_timing(struct fb_info *p)
{
	unsigned hd = p->var.xres / 8;
	unsigned hs = (p->var.xres + p->var.right_margin) / 8;
       	unsigned he = (p->var.xres + p->var.right_margin + p->var.hsync_len) / 8;
	unsigned ht = (p->var.left_margin + p->var.xres + p->var.right_margin + p->var.hsync_len) / 8;
	unsigned vd = p->var.yres;
	unsigned vs = p->var.yres + p->var.lower_margin;
	unsigned ve = p->var.yres + p->var.lower_margin + p->var.vsync_len;
	unsigned vt = p->var.upper_margin + p->var.yres + p->var.lower_margin + p->var.vsync_len;
	unsigned wd = (p->var.xres_virtual * ((p->var.bits_per_pixel+7)/8)) / 8;

	if ((p->var.xres == 640) && (p->var.yres == 480) && (p->var.pixclock == 39722)) {
	  write_fr(0x01, 0x02);  /* LCD */
	} else {
	  write_fr(0x01, 0x01);  /* CRT */
	}

	write_cr(0x11, (ve - 1) & 0x0f);
	write_cr(0x00, (ht - 5) & 0xff);
	write_cr(0x01, hd - 1);
	write_cr(0x02, hd);
	write_cr(0x03, ((ht - 1) & 0x1f) | 0x80);
	write_cr(0x04, hs);
	write_cr(0x05, (((ht - 1) & 0x20) <<2) | (he & 0x1f));
	write_cr(0x3c, (ht - 1) & 0xc0);
	write_cr(0x06, (vt - 2) & 0xff);
	write_cr(0x30, (vt - 2) >> 8);
	write_cr(0x07, 0x00);
	write_cr(0x08, 0x00);
	write_cr(0x09, 0x00);
	write_cr(0x10, (vs - 1) & 0xff);
	write_cr(0x32, ((vs - 1) >> 8) & 0xf);
	write_cr(0x11, ((ve - 1) & 0x0f) | 0x80);
	write_cr(0x12, (vd - 1) & 0xff);
	write_cr(0x31, ((vd - 1) & 0xf00) >> 8);
	write_cr(0x13, wd & 0xff);
	write_cr(0x41, (wd & 0xf00) >> 8);
	write_cr(0x15, (vs - 1) & 0xff);
	write_cr(0x33, ((vs - 1) >> 8) & 0xf);
	write_cr(0x38, ((ht - 5) & 0x100) >> 8);
	write_cr(0x16, (vt - 1) & 0xff);
	write_cr(0x18, 0x00);

	if (p->var.xres == 640) {
	  writeb(0xc7, mmio_base + 0x784);	/* set misc output reg */
	} else {
	  writeb(0x07, mmio_base + 0x784);	/* set misc output reg */
	}
}