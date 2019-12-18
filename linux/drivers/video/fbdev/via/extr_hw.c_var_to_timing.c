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
typedef  int u16 ;
struct via_display_timing {int hor_addr; int hor_sync_start; int hor_sync_end; int hor_total; int hor_blank_start; int hor_blank_end; int ver_addr; int ver_sync_start; int ver_sync_end; int ver_total; int ver_blank_start; int ver_blank_end; } ;
struct fb_var_screeninfo {int xres; int yres; int right_margin; int hsync_len; int left_margin; int lower_margin; int vsync_len; int upper_margin; } ;

/* Variables and functions */

struct via_display_timing var_to_timing(const struct fb_var_screeninfo *var,
	u16 cxres, u16 cyres)
{
	struct via_display_timing timing;
	u16 dx = (var->xres - cxres) / 2, dy = (var->yres - cyres) / 2;

	timing.hor_addr = cxres;
	timing.hor_sync_start = timing.hor_addr + var->right_margin + dx;
	timing.hor_sync_end = timing.hor_sync_start + var->hsync_len;
	timing.hor_total = timing.hor_sync_end + var->left_margin + dx;
	timing.hor_blank_start = timing.hor_addr + dx;
	timing.hor_blank_end = timing.hor_total - dx;
	timing.ver_addr = cyres;
	timing.ver_sync_start = timing.ver_addr + var->lower_margin + dy;
	timing.ver_sync_end = timing.ver_sync_start + var->vsync_len;
	timing.ver_total = timing.ver_sync_end + var->upper_margin + dy;
	timing.ver_blank_start = timing.ver_addr + dy;
	timing.ver_blank_end = timing.ver_total - dy;
	return timing;
}