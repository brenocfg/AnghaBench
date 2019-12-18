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
struct vc_data {int /*<<< orphan*/  vc_visible_origin; int /*<<< orphan*/  vc_origin; } ;

/* Variables and functions */
 scalar_t__ console_blanked ; 
 scalar_t__ vga_is_gfx ; 
 int /*<<< orphan*/  vga_palette_blanked ; 
 scalar_t__ vga_rolled_over ; 
 int /*<<< orphan*/  vga_set_mem_top (struct vc_data*) ; 
 int /*<<< orphan*/  vga_vram_base ; 

__attribute__((used)) static int vgacon_set_origin(struct vc_data *c)
{
	if (vga_is_gfx ||	/* We don't play origin tricks in graphic modes */
	    (console_blanked && !vga_palette_blanked))	/* Nor we write to blanked screens */
		return 0;
	c->vc_origin = c->vc_visible_origin = vga_vram_base;
	vga_set_mem_top(c);
	vga_rolled_over = 0;
	return 1;
}