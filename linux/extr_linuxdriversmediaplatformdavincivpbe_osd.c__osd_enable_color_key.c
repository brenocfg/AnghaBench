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
struct osd_state {int /*<<< orphan*/  vpbe_type; } ;
typedef  enum osd_win_layer { ____Placeholder_osd_win_layer } osd_win_layer ;
typedef  enum osd_pix_format { ____Placeholder_osd_pix_format } osd_pix_format ;

/* Variables and functions */
#define  OSDWIN_OSD0 137 
#define  OSDWIN_OSD1 136 
 int /*<<< orphan*/  OSD_OSDWIN0MD ; 
 int /*<<< orphan*/  OSD_OSDWIN0MD_TE0 ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD_TE1 ; 
 int /*<<< orphan*/  OSD_TRANSPBMPIDX ; 
 int /*<<< orphan*/  OSD_TRANSPBMPIDX_BMP0 ; 
 unsigned int OSD_TRANSPBMPIDX_BMP0_SHIFT ; 
 int /*<<< orphan*/  OSD_TRANSPBMPIDX_BMP1 ; 
 unsigned int OSD_TRANSPBMPIDX_BMP1_SHIFT ; 
 int /*<<< orphan*/  OSD_TRANSPVAL ; 
 int /*<<< orphan*/  OSD_TRANSPVALL ; 
 unsigned int OSD_TRANSPVALL_RGBL ; 
 int /*<<< orphan*/  OSD_TRANSPVALU ; 
 int /*<<< orphan*/  OSD_TRANSPVALU_RGBU ; 
 int /*<<< orphan*/  OSD_TRANSPVALU_Y ; 
 unsigned int OSD_TRANSPVAL_RGBTRANS ; 
#define  PIXFMT_1BPP 135 
#define  PIXFMT_2BPP 134 
#define  PIXFMT_4BPP 133 
#define  PIXFMT_8BPP 132 
#define  PIXFMT_RGB565 131 
#define  PIXFMT_RGB888 130 
#define  PIXFMT_YCBCRI 129 
#define  PIXFMT_YCRCBI 128 
 int /*<<< orphan*/  VPBE_VERSION_1 ; 
 int /*<<< orphan*/  VPBE_VERSION_3 ; 
 int /*<<< orphan*/  osd_modify (struct osd_state*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_set (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_write (struct osd_state*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_enable_color_key(struct osd_state *sd,
				  enum osd_win_layer osdwin,
				  unsigned colorkey,
				  enum osd_pix_format pixfmt)
{
	switch (pixfmt) {
	case PIXFMT_1BPP:
	case PIXFMT_2BPP:
	case PIXFMT_4BPP:
	case PIXFMT_8BPP:
		if (sd->vpbe_type == VPBE_VERSION_3) {
			switch (osdwin) {
			case OSDWIN_OSD0:
				osd_modify(sd, OSD_TRANSPBMPIDX_BMP0,
					  colorkey <<
					  OSD_TRANSPBMPIDX_BMP0_SHIFT,
					  OSD_TRANSPBMPIDX);
				break;
			case OSDWIN_OSD1:
				osd_modify(sd, OSD_TRANSPBMPIDX_BMP1,
					  colorkey <<
					  OSD_TRANSPBMPIDX_BMP1_SHIFT,
					  OSD_TRANSPBMPIDX);
				break;
			}
		}
		break;
	case PIXFMT_RGB565:
		if (sd->vpbe_type == VPBE_VERSION_1)
			osd_write(sd, colorkey & OSD_TRANSPVAL_RGBTRANS,
				  OSD_TRANSPVAL);
		else if (sd->vpbe_type == VPBE_VERSION_3)
			osd_write(sd, colorkey & OSD_TRANSPVALL_RGBL,
				  OSD_TRANSPVALL);
		break;
	case PIXFMT_YCBCRI:
	case PIXFMT_YCRCBI:
		if (sd->vpbe_type == VPBE_VERSION_3)
			osd_modify(sd, OSD_TRANSPVALU_Y, colorkey,
				   OSD_TRANSPVALU);
		break;
	case PIXFMT_RGB888:
		if (sd->vpbe_type == VPBE_VERSION_3) {
			osd_write(sd, colorkey & OSD_TRANSPVALL_RGBL,
				  OSD_TRANSPVALL);
			osd_modify(sd, OSD_TRANSPVALU_RGBU, colorkey >> 16,
				  OSD_TRANSPVALU);
		}
		break;
	default:
		break;
	}

	switch (osdwin) {
	case OSDWIN_OSD0:
		osd_set(sd, OSD_OSDWIN0MD_TE0, OSD_OSDWIN0MD);
		break;
	case OSDWIN_OSD1:
		osd_set(sd, OSD_OSDWIN1MD_TE1, OSD_OSDWIN1MD);
		break;
	}
}