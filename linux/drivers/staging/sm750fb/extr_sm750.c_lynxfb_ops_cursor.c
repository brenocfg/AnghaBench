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
typedef  int u16 ;
struct lynx_cursor {scalar_t__ maxW; scalar_t__ maxH; } ;
struct lynxfb_crtc {struct lynx_cursor cursor; } ;
struct lynxfb_par {struct lynxfb_crtc crtc; } ;
struct TYPE_5__ {int* red; int* green; int* blue; } ;
struct TYPE_4__ {scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct fb_info {TYPE_2__ cmap; TYPE_1__ var; struct lynxfb_par* par; } ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; int depth; size_t fg_color; size_t bg_color; int /*<<< orphan*/  data; scalar_t__ dy; scalar_t__ dx; } ;
struct fb_cursor {int set; scalar_t__ enable; int /*<<< orphan*/  mask; TYPE_3__ image; int /*<<< orphan*/  rop; } ;

/* Variables and functions */
 int ENXIO ; 
 int FB_CUR_SETCMAP ; 
 int FB_CUR_SETIMAGE ; 
 int FB_CUR_SETPOS ; 
 int FB_CUR_SETSHAPE ; 
 int FB_CUR_SETSIZE ; 
 int /*<<< orphan*/  sm750_hw_cursor_disable (struct lynx_cursor*) ; 
 int /*<<< orphan*/  sm750_hw_cursor_enable (struct lynx_cursor*) ; 
 int /*<<< orphan*/  sm750_hw_cursor_setColor (struct lynx_cursor*,int,int) ; 
 int /*<<< orphan*/  sm750_hw_cursor_setData (struct lynx_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm750_hw_cursor_setPos (struct lynx_cursor*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sm750_hw_cursor_setSize (struct lynx_cursor*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lynxfb_ops_cursor(struct fb_info *info, struct fb_cursor *fbcursor)
{
	struct lynxfb_par *par;
	struct lynxfb_crtc *crtc;
	struct lynx_cursor *cursor;

	par = info->par;
	crtc = &par->crtc;
	cursor = &crtc->cursor;

	if (fbcursor->image.width > cursor->maxW ||
	    fbcursor->image.height > cursor->maxH ||
	    fbcursor->image.depth > 1) {
		return -ENXIO;
	}

	sm750_hw_cursor_disable(cursor);
	if (fbcursor->set & FB_CUR_SETSIZE)
		sm750_hw_cursor_setSize(cursor,
					fbcursor->image.width,
					fbcursor->image.height);

	if (fbcursor->set & FB_CUR_SETPOS)
		sm750_hw_cursor_setPos(cursor,
				       fbcursor->image.dx - info->var.xoffset,
				       fbcursor->image.dy - info->var.yoffset);

	if (fbcursor->set & FB_CUR_SETCMAP) {
		/* get the 16bit color of kernel means */
		u16 fg, bg;

		fg = ((info->cmap.red[fbcursor->image.fg_color] & 0xf800)) |
		     ((info->cmap.green[fbcursor->image.fg_color] & 0xfc00) >> 5) |
		     ((info->cmap.blue[fbcursor->image.fg_color] & 0xf800) >> 11);

		bg = ((info->cmap.red[fbcursor->image.bg_color] & 0xf800)) |
		     ((info->cmap.green[fbcursor->image.bg_color] & 0xfc00) >> 5) |
		     ((info->cmap.blue[fbcursor->image.bg_color] & 0xf800) >> 11);

		sm750_hw_cursor_setColor(cursor, fg, bg);
	}

	if (fbcursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) {
		sm750_hw_cursor_setData(cursor,
					fbcursor->rop,
					fbcursor->image.data,
					fbcursor->mask);
	}

	if (fbcursor->enable)
		sm750_hw_cursor_enable(cursor);

	return 0;
}