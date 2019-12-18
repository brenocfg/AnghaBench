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
struct vgastate {int /*<<< orphan*/  vgabase; scalar_t__ vidstate; } ;
struct regstate {int* vga_cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_PEL_D ; 
 int /*<<< orphan*/  VGA_PEL_IW ; 
 int /*<<< orphan*/  VGA_PEL_MSK ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void restore_vga_cmap(struct vgastate *state)
{
	struct regstate *saved = (struct regstate *) state->vidstate;
	int i;

	vga_w(state->vgabase, VGA_PEL_MSK, 0xff);

	/* assumes DAC is readable and writable */
	vga_w(state->vgabase, VGA_PEL_IW, 0x00);
	for (i = 0; i < 768; i++)
		vga_w(state->vgabase, VGA_PEL_D, saved->vga_cmap[i]);
}