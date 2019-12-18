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
typedef  int /*<<< orphan*/  u32 ;
struct osd_state {int dummy; } ;
typedef  enum osd_win_layer { ____Placeholder_osd_win_layer } osd_win_layer ;
typedef  enum osd_pix_format { ____Placeholder_osd_pix_format } osd_pix_format ;

/* Variables and functions */
#define  OSDWIN_OSD0 132 
#define  OSDWIN_OSD1 131 
 int /*<<< orphan*/  OSD_W0BMP01 ; 
 int /*<<< orphan*/  OSD_W1BMP01 ; 
#define  PIXFMT_1BPP 130 
#define  PIXFMT_2BPP 129 
#define  PIXFMT_4BPP 128 
 int /*<<< orphan*/  osd_modify (struct osd_state*,int,unsigned char,int) ; 

__attribute__((used)) static void _osd_set_palette_map(struct osd_state *sd,
				 enum osd_win_layer osdwin,
				 unsigned char pixel_value,
				 unsigned char clut_index,
				 enum osd_pix_format pixfmt)
{
	static const int map_2bpp[] = { 0, 5, 10, 15 };
	static const int map_1bpp[] = { 0, 15 };
	int bmp_offset;
	int bmp_shift;
	int bmp_mask;
	int bmp_reg;

	switch (pixfmt) {
	case PIXFMT_1BPP:
		bmp_reg = map_1bpp[pixel_value & 0x1];
		break;
	case PIXFMT_2BPP:
		bmp_reg = map_2bpp[pixel_value & 0x3];
		break;
	case PIXFMT_4BPP:
		bmp_reg = pixel_value & 0xf;
		break;
	default:
		return;
	}

	switch (osdwin) {
	case OSDWIN_OSD0:
		bmp_offset = OSD_W0BMP01 + (bmp_reg >> 1) * sizeof(u32);
		break;
	case OSDWIN_OSD1:
		bmp_offset = OSD_W1BMP01 + (bmp_reg >> 1) * sizeof(u32);
		break;
	default:
		return;
	}

	if (bmp_reg & 1) {
		bmp_shift = 8;
		bmp_mask = 0xff << 8;
	} else {
		bmp_shift = 0;
		bmp_mask = 0xff;
	}

	osd_modify(sd, bmp_mask, clut_index << bmp_shift, bmp_offset);
}