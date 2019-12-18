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
struct vgastate {int /*<<< orphan*/  vgabase; } ;

/* Variables and functions */
 int vga_rcrt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vgaHWLock(struct vgastate *state)
{
	/* Protect CRTC[0-7] */
	vga_wcrt(state->vgabase, 0x11, vga_rcrt(state->vgabase, 0x11) | 0x80);
}