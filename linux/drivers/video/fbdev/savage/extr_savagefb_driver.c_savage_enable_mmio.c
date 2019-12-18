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
struct savagefb_par {scalar_t__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ S3_SAVAGE4 ; 
 unsigned char vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,unsigned char,struct savagefb_par*) ; 

__attribute__((used)) static void savage_enable_mmio(struct savagefb_par *par)
{
	unsigned char val;

	DBG("savage_enable_mmio\n");

	val = vga_in8(0x3c3, par);
	vga_out8(0x3c3, val | 0x01, par);
	val = vga_in8(0x3cc, par);
	vga_out8(0x3c2, val | 0x01, par);

	if (par->chip >= S3_SAVAGE4) {
		vga_out8(0x3d4, 0x40, par);
		val = vga_in8(0x3d5, par);
		vga_out8(0x3d5, val | 1, par);
	}
}