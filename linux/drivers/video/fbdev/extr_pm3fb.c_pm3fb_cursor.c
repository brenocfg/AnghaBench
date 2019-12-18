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
struct pm3_par {int dummy; } ;
struct fb_cmap {int* red; int* green; int* blue; } ;
struct TYPE_4__ {int xoffset; int yoffset; } ;
struct fb_info {struct fb_cmap cmap; TYPE_1__ var; struct pm3_par* par; } ;
struct TYPE_6__ {int width; int height; int depth; int dx; int dy; size_t fg_color; size_t bg_color; scalar_t__ data; } ;
struct TYPE_5__ {int x; int y; } ;
struct fb_cursor {int set; scalar_t__ rop; TYPE_3__ image; scalar_t__ mask; TYPE_2__ hot; scalar_t__ enable; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_CUR_SETCMAP ; 
 int FB_CUR_SETHOT ; 
 int FB_CUR_SETIMAGE ; 
 int FB_CUR_SETPOS ; 
 int FB_CUR_SETSHAPE ; 
 int /*<<< orphan*/  PM3RD_CursorHotSpotX ; 
 int /*<<< orphan*/  PM3RD_CursorHotSpotY ; 
 int /*<<< orphan*/  PM3RD_CursorMode ; 
 int PM3RD_CursorMode_CURSOR_ENABLE ; 
 int PM3RD_CursorMode_TYPE_X ; 
 int /*<<< orphan*/  PM3RD_CursorPalette (int) ; 
 int PM3RD_CursorPattern (int) ; 
 int /*<<< orphan*/  PM3RD_CursorXHigh ; 
 int /*<<< orphan*/  PM3RD_CursorXLow ; 
 int /*<<< orphan*/  PM3RD_CursorYHigh ; 
 int /*<<< orphan*/  PM3RD_CursorYLow ; 
 int /*<<< orphan*/  PM3_WRITE_DAC_REG (struct pm3_par*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ROP_COPY ; 
 int* cursor_bits_lookup ; 
 int /*<<< orphan*/  hwcursor ; 

__attribute__((used)) static int pm3fb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	struct pm3_par *par = info->par;
	u8 mode;

	if (!hwcursor)
		return -EINVAL;	/* just to force soft_cursor() call */

	/* Too large of a cursor or wrong bpp :-( */
	if (cursor->image.width > 64 ||
	    cursor->image.height > 64 ||
	    cursor->image.depth > 1)
		return -EINVAL;

	mode = PM3RD_CursorMode_TYPE_X;
	if (cursor->enable)
		 mode |= PM3RD_CursorMode_CURSOR_ENABLE;

	PM3_WRITE_DAC_REG(par, PM3RD_CursorMode, mode);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (if enable is set) or we want to query what
	 * we can do with the cursor (if enable is not set)
	 */
	if (!cursor->set)
		return 0;

	if (cursor->set & FB_CUR_SETPOS) {
		int x = cursor->image.dx - info->var.xoffset;
		int y = cursor->image.dy - info->var.yoffset;

		PM3_WRITE_DAC_REG(par, PM3RD_CursorXLow, x & 0xff);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorXHigh, (x >> 8) & 0xf);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorYLow, y & 0xff);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorYHigh, (y >> 8) & 0xf);
	}

	if (cursor->set & FB_CUR_SETHOT) {
		PM3_WRITE_DAC_REG(par, PM3RD_CursorHotSpotX,
				  cursor->hot.x & 0x3f);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorHotSpotY,
				  cursor->hot.y & 0x3f);
	}

	if (cursor->set & FB_CUR_SETCMAP) {
		u32 fg_idx = cursor->image.fg_color;
		u32 bg_idx = cursor->image.bg_color;
		struct fb_cmap cmap = info->cmap;

		/* the X11 driver says one should use these color registers */
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(39),
				  cmap.red[fg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(40),
				  cmap.green[fg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(41),
				  cmap.blue[fg_idx] >> 8 );

		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(42),
				  cmap.red[bg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(43),
				  cmap.green[bg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(44),
				  cmap.blue[bg_idx] >> 8 );
	}

	if (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) {
		u8 *bitmap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		int i;
		int pos = PM3RD_CursorPattern(0);

		for (i = 0; i < cursor->image.height; i++) {
			int j = (cursor->image.width + 7) >> 3;
			int k = 8 - j;

			for (; j > 0; j--) {
				u8 data = *bitmap ^ *mask;

				if (cursor->rop == ROP_COPY)
					data = *mask & *bitmap;
				/* Upper 4 bits of bitmap data */
				PM3_WRITE_DAC_REG(par, pos++,
					cursor_bits_lookup[data >> 4] |
					(cursor_bits_lookup[*mask >> 4] << 1));
				/* Lower 4 bits of bitmap */
				PM3_WRITE_DAC_REG(par, pos++,
					cursor_bits_lookup[data & 0xf] |
					(cursor_bits_lookup[*mask & 0xf] << 1));
				bitmap++;
				mask++;
			}
			for (; k > 0; k--) {
				PM3_WRITE_DAC_REG(par, pos++, 0);
				PM3_WRITE_DAC_REG(par, pos++, 0);
			}
		}
		while (pos < PM3RD_CursorPattern(1024))
			PM3_WRITE_DAC_REG(par, pos++, 0);
	}
	return 0;
}