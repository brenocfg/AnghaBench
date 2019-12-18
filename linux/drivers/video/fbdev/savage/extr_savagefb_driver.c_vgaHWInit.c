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
struct xtimings {int sync; int HTotal; int HDisplay; int HSyncStart; int HSyncEnd; int VTotal; int VDisplay; int VSyncStart; int VSyncEnd; scalar_t__ dblscan; } ;
struct savagefb_par {int dummy; } ;
struct savage_reg {int MiscOutReg; int* Sequencer; int* CRTC; int* Graphics; int* Attribute; } ;
struct fb_var_screeninfo {int xres_virtual; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 

__attribute__((used)) static void vgaHWInit(struct fb_var_screeninfo *var,
		      struct savagefb_par            *par,
		      struct xtimings                *timings,
		      struct savage_reg              *reg)
{
	reg->MiscOutReg = 0x23;

	if (!(timings->sync & FB_SYNC_HOR_HIGH_ACT))
		reg->MiscOutReg |= 0x40;

	if (!(timings->sync & FB_SYNC_VERT_HIGH_ACT))
		reg->MiscOutReg |= 0x80;

	/*
	 * Time Sequencer
	 */
	reg->Sequencer[0x00] = 0x00;
	reg->Sequencer[0x01] = 0x01;
	reg->Sequencer[0x02] = 0x0F;
	reg->Sequencer[0x03] = 0x00;          /* Font select */
	reg->Sequencer[0x04] = 0x0E;          /* Misc */

	/*
	 * CRTC Controller
	 */
	reg->CRTC[0x00] = (timings->HTotal >> 3) - 5;
	reg->CRTC[0x01] = (timings->HDisplay >> 3) - 1;
	reg->CRTC[0x02] = (timings->HSyncStart >> 3) - 1;
	reg->CRTC[0x03] = (((timings->HSyncEnd >> 3)  - 1) & 0x1f) | 0x80;
	reg->CRTC[0x04] = (timings->HSyncStart >> 3);
	reg->CRTC[0x05] = ((((timings->HSyncEnd >> 3) - 1) & 0x20) << 2) |
		(((timings->HSyncEnd >> 3)) & 0x1f);
	reg->CRTC[0x06] = (timings->VTotal - 2) & 0xFF;
	reg->CRTC[0x07] = (((timings->VTotal - 2) & 0x100) >> 8) |
		(((timings->VDisplay - 1) & 0x100) >> 7) |
		((timings->VSyncStart & 0x100) >> 6) |
		(((timings->VSyncStart - 1) & 0x100) >> 5) |
		0x10 |
		(((timings->VTotal - 2) & 0x200) >> 4) |
		(((timings->VDisplay - 1) & 0x200) >> 3) |
		((timings->VSyncStart & 0x200) >> 2);
	reg->CRTC[0x08] = 0x00;
	reg->CRTC[0x09] = (((timings->VSyncStart - 1) & 0x200) >> 4) | 0x40;

	if (timings->dblscan)
		reg->CRTC[0x09] |= 0x80;

	reg->CRTC[0x0a] = 0x00;
	reg->CRTC[0x0b] = 0x00;
	reg->CRTC[0x0c] = 0x00;
	reg->CRTC[0x0d] = 0x00;
	reg->CRTC[0x0e] = 0x00;
	reg->CRTC[0x0f] = 0x00;
	reg->CRTC[0x10] = timings->VSyncStart & 0xff;
	reg->CRTC[0x11] = (timings->VSyncEnd & 0x0f) | 0x20;
	reg->CRTC[0x12] = (timings->VDisplay - 1) & 0xff;
	reg->CRTC[0x13] = var->xres_virtual >> 4;
	reg->CRTC[0x14] = 0x00;
	reg->CRTC[0x15] = (timings->VSyncStart - 1) & 0xff;
	reg->CRTC[0x16] = (timings->VSyncEnd - 1) & 0xff;
	reg->CRTC[0x17] = 0xc3;
	reg->CRTC[0x18] = 0xff;

	/*
	 * are these unnecessary?
	 * vgaHWHBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN|KGA_ENABLE_ON_ZERO);
	 * vgaHWVBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN|KGA_ENABLE_ON_ZERO);
	 */

	/*
	 * Graphics Display Controller
	 */
	reg->Graphics[0x00] = 0x00;
	reg->Graphics[0x01] = 0x00;
	reg->Graphics[0x02] = 0x00;
	reg->Graphics[0x03] = 0x00;
	reg->Graphics[0x04] = 0x00;
	reg->Graphics[0x05] = 0x40;
	reg->Graphics[0x06] = 0x05;   /* only map 64k VGA memory !!!! */
	reg->Graphics[0x07] = 0x0F;
	reg->Graphics[0x08] = 0xFF;


	reg->Attribute[0x00]  = 0x00; /* standard colormap translation */
	reg->Attribute[0x01]  = 0x01;
	reg->Attribute[0x02]  = 0x02;
	reg->Attribute[0x03]  = 0x03;
	reg->Attribute[0x04]  = 0x04;
	reg->Attribute[0x05]  = 0x05;
	reg->Attribute[0x06]  = 0x06;
	reg->Attribute[0x07]  = 0x07;
	reg->Attribute[0x08]  = 0x08;
	reg->Attribute[0x09]  = 0x09;
	reg->Attribute[0x0a] = 0x0A;
	reg->Attribute[0x0b] = 0x0B;
	reg->Attribute[0x0c] = 0x0C;
	reg->Attribute[0x0d] = 0x0D;
	reg->Attribute[0x0e] = 0x0E;
	reg->Attribute[0x0f] = 0x0F;
	reg->Attribute[0x10] = 0x41;
	reg->Attribute[0x11] = 0xFF;
	reg->Attribute[0x12] = 0x0F;
	reg->Attribute[0x13] = 0x00;
	reg->Attribute[0x14] = 0x00;
}