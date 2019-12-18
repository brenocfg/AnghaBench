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
typedef  int u8 ;
struct tridentfb_par {int /*<<< orphan*/  io_virt; } ;

/* Variables and functions */
 int DDC_MASK_TGUI ; 
 int DDC_SDA_DRIVE_TGUI ; 
 int /*<<< orphan*/  I2C ; 
 int vga_mm_rcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_mm_wcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tridentfb_ddc_setsda_tgui(void *data, int val)
{
	struct tridentfb_par *par = data;
	u8 reg = vga_mm_rcrt(par->io_virt, I2C) & DDC_MASK_TGUI;

	if (val)
		reg &= ~DDC_SDA_DRIVE_TGUI; /* disable drive - don't drive hi */
	else
		reg |= DDC_SDA_DRIVE_TGUI; /* drive low */

	vga_mm_wcrt(par->io_virt, I2C, reg);
}