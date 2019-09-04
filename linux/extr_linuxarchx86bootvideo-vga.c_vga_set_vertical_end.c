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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  out_idx (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_crtc () ; 

__attribute__((used)) static void vga_set_vertical_end(int lines)
{
	u16 crtc;		/* CRTC base address */
	u8  ovfw;		/* CRTC overflow register */
	int end = lines-1;

	crtc = vga_crtc();

	ovfw = 0x3c | ((end >> (8-1)) & 0x02) | ((end >> (9-6)) & 0x40);

	out_idx(ovfw, crtc, 0x07); /* Vertical overflow */
	out_idx(end,  crtc, 0x12); /* Vertical display end */
}