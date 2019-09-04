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
struct osd_layer_config {int pixfmt; int line_length; int xsize; int ysize; int xpos; int ypos; int interlaced; } ;
struct osd_window_state {struct osd_layer_config lconfig; } ;
struct osd_state {scalar_t__ vpbe_type; struct osd_window_state* win; } ;
typedef  enum osd_pix_format { ____Placeholder_osd_pix_format } osd_pix_format ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 scalar_t__ MAX_LINE_LENGTH ; 
 scalar_t__ MAX_WIN_SIZE ; 
#define  PIXFMT_1BPP 137 
#define  PIXFMT_2BPP 136 
#define  PIXFMT_4BPP 135 
#define  PIXFMT_8BPP 134 
#define  PIXFMT_NV12 133 
#define  PIXFMT_OSD_ATTR 132 
#define  PIXFMT_RGB565 131 
#define  PIXFMT_RGB888 130 
#define  PIXFMT_YCBCRI 129 
#define  PIXFMT_YCRCBI 128 
 scalar_t__ VPBE_VERSION_1 ; 
 scalar_t__ VPBE_VERSION_2 ; 
 scalar_t__ VPBE_VERSION_3 ; 
 int WIN_OSD0 ; 
 int WIN_OSD1 ; 
 int WIN_VID0 ; 
 size_t WIN_VID1 ; 
 int is_osd_win (int) ; 
 scalar_t__ is_rgb_pixfmt (int) ; 
 scalar_t__ is_vid_win (int) ; 
 void* min (int,unsigned int) ; 

__attribute__((used)) static int try_layer_config(struct osd_state *sd, enum osd_layer layer,
			    struct osd_layer_config *lconfig)
{
	struct osd_state *osd = sd;
	struct osd_window_state *win = &osd->win[layer];
	int bad_config = 0;

	/* verify that the pixel format is compatible with the layer */
	switch (lconfig->pixfmt) {
	case PIXFMT_1BPP:
	case PIXFMT_2BPP:
	case PIXFMT_4BPP:
	case PIXFMT_8BPP:
	case PIXFMT_RGB565:
		if (osd->vpbe_type == VPBE_VERSION_1)
			bad_config = !is_vid_win(layer);
		break;
	case PIXFMT_YCBCRI:
	case PIXFMT_YCRCBI:
		bad_config = !is_vid_win(layer);
		break;
	case PIXFMT_RGB888:
		if (osd->vpbe_type == VPBE_VERSION_1)
			bad_config = !is_vid_win(layer);
		else if ((osd->vpbe_type == VPBE_VERSION_3) ||
			 (osd->vpbe_type == VPBE_VERSION_2))
			bad_config = !is_osd_win(layer);
		break;
	case PIXFMT_NV12:
		if (osd->vpbe_type != VPBE_VERSION_2)
			bad_config = 1;
		else
			bad_config = is_osd_win(layer);
		break;
	case PIXFMT_OSD_ATTR:
		bad_config = (layer != WIN_OSD1);
		break;
	default:
		bad_config = 1;
		break;
	}
	if (bad_config) {
		/*
		 * The requested pixel format is incompatible with the layer,
		 * so keep the current layer configuration.
		 */
		*lconfig = win->lconfig;
		return bad_config;
	}

	/* DM6446: */
	/* only one OSD window at a time can use RGB pixel formats */
	if ((osd->vpbe_type == VPBE_VERSION_1) &&
	    is_osd_win(layer) && is_rgb_pixfmt(lconfig->pixfmt)) {
		enum osd_pix_format pixfmt;

		if (layer == WIN_OSD0)
			pixfmt = osd->win[WIN_OSD1].lconfig.pixfmt;
		else
			pixfmt = osd->win[WIN_OSD0].lconfig.pixfmt;

		if (is_rgb_pixfmt(pixfmt)) {
			/*
			 * The other OSD window is already configured for an
			 * RGB, so keep the current layer configuration.
			 */
			*lconfig = win->lconfig;
			return 1;
		}
	}

	/* DM6446: only one video window at a time can use RGB888 */
	if ((osd->vpbe_type == VPBE_VERSION_1) && is_vid_win(layer) &&
		lconfig->pixfmt == PIXFMT_RGB888) {
		enum osd_pix_format pixfmt;

		if (layer == WIN_VID0)
			pixfmt = osd->win[WIN_VID1].lconfig.pixfmt;
		else
			pixfmt = osd->win[WIN_VID0].lconfig.pixfmt;

		if (pixfmt == PIXFMT_RGB888) {
			/*
			 * The other video window is already configured for
			 * RGB888, so keep the current layer configuration.
			 */
			*lconfig = win->lconfig;
			return 1;
		}
	}

	/* window dimensions must be non-zero */
	if (!lconfig->line_length || !lconfig->xsize || !lconfig->ysize) {
		*lconfig = win->lconfig;
		return 1;
	}

	/* round line_length up to a multiple of 32 */
	lconfig->line_length = ((lconfig->line_length + 31) / 32) * 32;
	lconfig->line_length =
	    min(lconfig->line_length, (unsigned)MAX_LINE_LENGTH);
	lconfig->xsize = min(lconfig->xsize, (unsigned)MAX_WIN_SIZE);
	lconfig->ysize = min(lconfig->ysize, (unsigned)MAX_WIN_SIZE);
	lconfig->xpos = min(lconfig->xpos, (unsigned)MAX_WIN_SIZE);
	lconfig->ypos = min(lconfig->ypos, (unsigned)MAX_WIN_SIZE);
	lconfig->interlaced = (lconfig->interlaced != 0);
	if (lconfig->interlaced) {
		/* ysize and ypos must be even for interlaced displays */
		lconfig->ysize &= ~1;
		lconfig->ypos &= ~1;
	}

	return 0;
}