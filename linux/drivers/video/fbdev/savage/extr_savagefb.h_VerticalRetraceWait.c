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
struct savagefb_par {int dummy; } ;

/* Variables and functions */
 int vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,int,struct savagefb_par*) ; 

__attribute__((used)) static inline void VerticalRetraceWait(struct savagefb_par *par)
{
	vga_out8(0x3d4, 0x17, par);
	if (vga_in8(0x3d5, par) & 0x80) {
		while ((vga_in8(0x3da, par) & 0x08) == 0x08);
		while ((vga_in8(0x3da, par) & 0x08) == 0x00);
	}
}