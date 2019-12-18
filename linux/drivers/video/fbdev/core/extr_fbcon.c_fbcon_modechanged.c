#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int height; } ;
struct vc_data {scalar_t__ vc_mode; size_t vc_num; TYPE_1__ vc_font; } ;
struct TYPE_6__ {scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct fbcon_ops {size_t currcon; int /*<<< orphan*/  (* update_start ) (struct fb_info*) ;TYPE_2__ var; int /*<<< orphan*/  rotate; } ;
struct fbcon_display {scalar_t__ yscroll; } ;
struct TYPE_8__ {int /*<<< orphan*/  xres; int /*<<< orphan*/  yres; } ;
struct fb_info {TYPE_4__ var; struct fbcon_ops* fbcon_par; } ;
struct TYPE_7__ {struct vc_data* d; } ;

/* Variables and functions */
 int FBCON_SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KD_TEXT ; 
 int /*<<< orphan*/  color_table ; 
 size_t* con2fb_map ; 
 scalar_t__ con_is_visible (struct vc_data*) ; 
 struct fbcon_display* fb_display ; 
 int /*<<< orphan*/  fbcon_is_inactive (struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_set_palette (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbcon_update_softback (struct vc_data*) ; 
 struct fb_info** registered_fb ; 
 scalar_t__ scrollback_current ; 
 scalar_t__ scrollback_max ; 
 int /*<<< orphan*/  set_blitting_type (struct vc_data*,struct fb_info*) ; 
 scalar_t__ softback_buf ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  update_screen (struct vc_data*) ; 
 int /*<<< orphan*/  updatescrollmode (struct fbcon_display*,struct fb_info*,struct vc_data*) ; 
 int /*<<< orphan*/  var_to_display (struct fbcon_display*,TYPE_4__*,struct fb_info*) ; 
 TYPE_3__* vc_cons ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int,int) ; 

__attribute__((used)) static void fbcon_modechanged(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;
	struct vc_data *vc;
	struct fbcon_display *p;
	int rows, cols;

	if (!ops || ops->currcon < 0)
		return;
	vc = vc_cons[ops->currcon].d;
	if (vc->vc_mode != KD_TEXT ||
	    registered_fb[con2fb_map[ops->currcon]] != info)
		return;

	p = &fb_display[vc->vc_num];
	set_blitting_type(vc, info);

	if (con_is_visible(vc)) {
		var_to_display(p, &info->var, info);
		cols = FBCON_SWAP(ops->rotate, info->var.xres, info->var.yres);
		rows = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
		cols /= vc->vc_font.width;
		rows /= vc->vc_font.height;
		vc_resize(vc, cols, rows);
		updatescrollmode(p, info, vc);
		scrollback_max = 0;
		scrollback_current = 0;

		if (!fbcon_is_inactive(vc, info)) {
		    ops->var.xoffset = ops->var.yoffset = p->yscroll = 0;
		    ops->update_start(info);
		}

		fbcon_set_palette(vc, color_table);
		update_screen(vc);
		if (softback_buf)
			fbcon_update_softback(vc);
	}
}