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
 int MDA_MODE_BLINK_EN ; 
 int MDA_MODE_VIDEO_EN ; 
 int /*<<< orphan*/  mda_gfx_port ; 
 int /*<<< orphan*/  mda_mode_port ; 
 int /*<<< orphan*/  mda_status_port ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_mda_b (int,int) ; 
 int /*<<< orphan*/  write_mda_w (int,int) ; 

__attribute__((used)) static void mda_initialize(void)
{
	write_mda_b(97, 0x00);		/* horizontal total */
	write_mda_b(80, 0x01);		/* horizontal displayed */
	write_mda_b(82, 0x02);		/* horizontal sync pos */
	write_mda_b(15, 0x03);		/* horizontal sync width */

	write_mda_b(25, 0x04);		/* vertical total */
	write_mda_b(6,  0x05);		/* vertical total adjust */
	write_mda_b(25, 0x06);		/* vertical displayed */
	write_mda_b(25, 0x07);		/* vertical sync pos */

	write_mda_b(2,  0x08);		/* interlace mode */
	write_mda_b(13, 0x09);		/* maximum scanline */
	write_mda_b(12, 0x0a);		/* cursor start */
	write_mda_b(13, 0x0b);		/* cursor end */

	write_mda_w(0x0000, 0x0c);	/* start address */
	write_mda_w(0x0000, 0x0e);	/* cursor location */

	outb_p(MDA_MODE_VIDEO_EN | MDA_MODE_BLINK_EN, mda_mode_port);
	outb_p(0x00, mda_status_port);
	outb_p(0x00, mda_gfx_port);
}