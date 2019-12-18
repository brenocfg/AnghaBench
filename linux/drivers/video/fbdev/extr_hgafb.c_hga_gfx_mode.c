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

/* Variables and functions */
 int /*<<< orphan*/  HGA_GFX ; 
 int HGA_GFX_MODE_EN ; 
 int /*<<< orphan*/  HGA_GFX_PORT ; 
 int HGA_MODE_GRAPHICS ; 
 int /*<<< orphan*/  HGA_MODE_PORT ; 
 int HGA_MODE_VIDEO_EN ; 
 int /*<<< orphan*/  HGA_STATUS_PORT ; 
 int /*<<< orphan*/  hga_mode ; 
 int /*<<< orphan*/  hga_reg_lock ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_hga_b (int,int) ; 
 int /*<<< orphan*/  write_hga_w (int,int) ; 

__attribute__((used)) static void hga_gfx_mode(void)
{
	unsigned long flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	outb_p(0x00, HGA_STATUS_PORT);
	outb_p(HGA_GFX_MODE_EN, HGA_GFX_PORT);
	outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GRAPHICS, HGA_MODE_PORT);

	write_hga_b(0x35, 0x00);	/* horizontal total */
	write_hga_b(0x2d, 0x01);	/* horizontal displayed */
	write_hga_b(0x2e, 0x02);	/* horizontal sync pos */
	write_hga_b(0x07, 0x03);	/* horizontal sync width */

	write_hga_b(0x5b, 0x04);	/* vertical total */
	write_hga_b(0x02, 0x05);	/* vertical total adjust */
	write_hga_b(0x57, 0x06);	/* vertical displayed */
	write_hga_b(0x57, 0x07);	/* vertical sync pos */

	write_hga_b(0x02, 0x08);	/* interlace mode */
	write_hga_b(0x03, 0x09);	/* maximum scanline */
	write_hga_b(0x00, 0x0a);	/* cursor start */
	write_hga_b(0x00, 0x0b);	/* cursor end */

	write_hga_w(0x0000, 0x0c);	/* start address */
	write_hga_w(0x0000, 0x0e);	/* cursor location */

	hga_mode = HGA_GFX;
	spin_unlock_irqrestore(&hga_reg_lock, flags);
}