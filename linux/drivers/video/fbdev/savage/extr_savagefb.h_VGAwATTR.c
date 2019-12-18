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
struct savagefb_par {scalar_t__ paletteEnabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,int,struct savagefb_par*) ; 

__attribute__((used)) static inline void VGAwATTR(u8 index, u8 value, struct savagefb_par *par)
{
	if (par->paletteEnabled)
		index &= ~0x20;
	else
		index |= 0x20;

	vga_in8(0x3da, par);
	vga_out8(0x3c0, index, par);
	vga_out8 (0x3c0, value, par);
}