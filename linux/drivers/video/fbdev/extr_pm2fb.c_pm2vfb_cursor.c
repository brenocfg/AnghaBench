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
typedef  int u8 ;
typedef  size_t u32 ;
struct pm2fb_par {int dummy; } ;
struct fb_cmap {int* red; int* green; int* blue; } ;
struct TYPE_4__ {int xoffset; int yoffset; } ;
struct fb_info {struct fb_cmap cmap; TYPE_1__ var; struct pm2fb_par* par; } ;
struct TYPE_6__ {int dx; int dy; size_t fg_color; size_t bg_color; int height; int width; scalar_t__ data; } ;
struct TYPE_5__ {int x; int y; } ;
struct fb_cursor {int set; scalar_t__ rop; TYPE_3__ image; scalar_t__ mask; TYPE_2__ hot; scalar_t__ enable; } ;

/* Variables and functions */
 int FB_CUR_SETCMAP ; 
 int FB_CUR_SETHOT ; 
 int FB_CUR_SETIMAGE ; 
 int FB_CUR_SETSHAPE ; 
 int PM2F_CURSORMODE_CURSOR_ENABLE ; 
 int PM2F_CURSORMODE_TYPE_X ; 
 int PM2VI_RD_CURSOR_MODE ; 
 int PM2VI_RD_CURSOR_PALETTE ; 
 int PM2VI_RD_CURSOR_PATTERN ; 
 int PM2VI_RD_CURSOR_X_HIGH ; 
 int PM2VI_RD_CURSOR_X_HOT ; 
 int PM2VI_RD_CURSOR_X_LOW ; 
 int PM2VI_RD_CURSOR_Y_HIGH ; 
 int PM2VI_RD_CURSOR_Y_HOT ; 
 int PM2VI_RD_CURSOR_Y_LOW ; 
 int /*<<< orphan*/  PM2VR_RD_INDEX_HIGH ; 
 scalar_t__ ROP_COPY ; 
 int* cursor_bits_lookup ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2v_RDAC_WR (struct pm2fb_par*,int,int) ; 

__attribute__((used)) static int pm2vfb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	struct pm2fb_par *par = info->par;
	u8 mode = PM2F_CURSORMODE_TYPE_X;
	int x = cursor->image.dx - info->var.xoffset;
	int y = cursor->image.dy - info->var.yoffset;

	if (cursor->enable)
		mode |= PM2F_CURSORMODE_CURSOR_ENABLE;

	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_MODE, mode);

	if (!cursor->enable)
		x = 2047;	/* push it outside display */
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_X_LOW, x & 0xff);
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_X_HIGH, (x >> 8) & 0xf);
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_Y_LOW, y & 0xff);
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_Y_HIGH, (y >> 8) & 0xf);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (if enable is set) or we want to query what
	 * we can do with the cursor (if enable is not set)
	 */
	if (!cursor->set)
		return 0;

	if (cursor->set & FB_CUR_SETHOT) {
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_X_HOT,
			     cursor->hot.x & 0x3f);
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_Y_HOT,
			     cursor->hot.y & 0x3f);
	}

	if (cursor->set & FB_CUR_SETCMAP) {
		u32 fg_idx = cursor->image.fg_color;
		u32 bg_idx = cursor->image.bg_color;
		struct fb_cmap cmap = info->cmap;

		/* the X11 driver says one should use these color registers */
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, PM2VI_RD_CURSOR_PALETTE >> 8);
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 0,
			     cmap.red[bg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 1,
			     cmap.green[bg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 2,
			     cmap.blue[bg_idx] >> 8 );

		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 3,
			     cmap.red[fg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 4,
			     cmap.green[fg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 5,
			     cmap.blue[fg_idx] >> 8 );
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
	}

	if (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) {
		u8 *bitmap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		int i;
		int pos = PM2VI_RD_CURSOR_PATTERN;

		for (i = 0; i < cursor->image.height; i++) {
			int j = (cursor->image.width + 7) >> 3;
			int k = 8 - j;

			pm2_WR(par, PM2VR_RD_INDEX_HIGH, pos >> 8);

			for (; j > 0; j--) {
				u8 data = *bitmap ^ *mask;

				if (cursor->rop == ROP_COPY)
					data = *mask & *bitmap;
				/* Upper 4 bits of bitmap data */
				pm2v_RDAC_WR(par, pos++,
					cursor_bits_lookup[data >> 4] |
					(cursor_bits_lookup[*mask >> 4] << 1));
				/* Lower 4 bits of bitmap */
				pm2v_RDAC_WR(par, pos++,
					cursor_bits_lookup[data & 0xf] |
					(cursor_bits_lookup[*mask & 0xf] << 1));
				bitmap++;
				mask++;
			}
			for (; k > 0; k--) {
				pm2v_RDAC_WR(par, pos++, 0);
				pm2v_RDAC_WR(par, pos++, 0);
			}
		}

		while (pos < (1024 + PM2VI_RD_CURSOR_PATTERN)) {
			pm2_WR(par, PM2VR_RD_INDEX_HIGH, pos >> 8);
			pm2v_RDAC_WR(par, pos++, 0);
		}

		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
	}
	return 0;
}