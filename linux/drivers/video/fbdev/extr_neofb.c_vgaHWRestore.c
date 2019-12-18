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
struct neofb_par {int* CRTC; int /*<<< orphan*/ * Attribute; int /*<<< orphan*/ * Graphics; int /*<<< orphan*/ * Sequencer; int /*<<< orphan*/  MiscOutReg; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  VGAdisablePalette () ; 
 int /*<<< orphan*/  VGAenablePalette () ; 
 int /*<<< orphan*/  VGAwATTR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vgaHWRestore(const struct fb_info *info,
			 const struct neofb_par *par)
{
	int i;

	vga_w(NULL, VGA_MIS_W, par->MiscOutReg);

	for (i = 1; i < 5; i++)
		vga_wseq(NULL, i, par->Sequencer[i]);

	/* Ensure CRTC registers 0-7 are unlocked by clearing bit 7 or CRTC[17] */
	vga_wcrt(NULL, 17, par->CRTC[17] & ~0x80);

	for (i = 0; i < 25; i++)
		vga_wcrt(NULL, i, par->CRTC[i]);

	for (i = 0; i < 9; i++)
		vga_wgfx(NULL, i, par->Graphics[i]);

	VGAenablePalette();

	for (i = 0; i < 21; i++)
		VGAwATTR(i, par->Attribute[i]);

	VGAdisablePalette();
}