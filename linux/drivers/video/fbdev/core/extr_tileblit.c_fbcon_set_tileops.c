#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct vc_data {TYPE_1__ vc_font; } ;
struct fbcon_ops {TYPE_2__* p; int /*<<< orphan*/  update_start; int /*<<< orphan*/  cursor; int /*<<< orphan*/  clear_margins; int /*<<< orphan*/  putcs; int /*<<< orphan*/  clear; int /*<<< orphan*/  bmove; } ;
struct fb_tilemap {int depth; int length; int /*<<< orphan*/  data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct fb_info {TYPE_3__* tileops; struct fbcon_ops* fbcon_par; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fb_settile ) (struct fb_info*,struct fb_tilemap*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  fontdata; scalar_t__ userfont; } ;

/* Variables and functions */
 int FNTCHARCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_tilemap*) ; 
 int /*<<< orphan*/  tile_bmove ; 
 int /*<<< orphan*/  tile_clear ; 
 int /*<<< orphan*/  tile_clear_margins ; 
 int /*<<< orphan*/  tile_cursor ; 
 int /*<<< orphan*/  tile_putcs ; 
 int /*<<< orphan*/  tile_update_start ; 

void fbcon_set_tileops(struct vc_data *vc, struct fb_info *info)
{
	struct fb_tilemap map;
	struct fbcon_ops *ops = info->fbcon_par;

	ops->bmove = tile_bmove;
	ops->clear = tile_clear;
	ops->putcs = tile_putcs;
	ops->clear_margins = tile_clear_margins;
	ops->cursor = tile_cursor;
	ops->update_start = tile_update_start;

	if (ops->p) {
		map.width = vc->vc_font.width;
		map.height = vc->vc_font.height;
		map.depth = 1;
		map.length = (ops->p->userfont) ?
			FNTCHARCNT(ops->p->fontdata) : 256;
		map.data = ops->p->fontdata;
		info->tileops->fb_settile(info, &map);
	}
}