#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgastate {int dummy; } ;
struct TYPE_3__ {int flags; } ;
struct vga16fb_par {int /*<<< orphan*/  ref_count; TYPE_1__ state; } ;
struct fb_info {struct vga16fb_par* par; } ;

/* Variables and functions */
 int VGA_SAVE_CMAP ; 
 int VGA_SAVE_FONTS ; 
 int VGA_SAVE_MODE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_vga (TYPE_1__*) ; 

__attribute__((used)) static int vga16fb_open(struct fb_info *info, int user)
{
	struct vga16fb_par *par = info->par;

	if (!par->ref_count) {
		memset(&par->state, 0, sizeof(struct vgastate));
		par->state.flags = VGA_SAVE_FONTS | VGA_SAVE_MODE |
			VGA_SAVE_CMAP;
		save_vga(&par->state);
	}
	par->ref_count++;

	return 0;
}