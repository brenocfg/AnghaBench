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
struct osd_layer_config {scalar_t__ pixfmt; } ;
struct osd_window_state {int /*<<< orphan*/  fb_base_phys; struct osd_layer_config lconfig; scalar_t__ is_enabled; } ;
struct osd_state {scalar_t__ yc_pixfmt; int /*<<< orphan*/  lock; int /*<<< orphan*/  field_inversion; int /*<<< orphan*/  pingpong; struct osd_window_state* win; struct osd_osdwin_state* osdwin; int /*<<< orphan*/  blink; int /*<<< orphan*/  is_blinking; } ;
struct osd_osdwin_state {unsigned char* palette_map; int /*<<< orphan*/  rec601_attenuation; int /*<<< orphan*/  colorkey; scalar_t__ colorkey_blending; int /*<<< orphan*/  blend; int /*<<< orphan*/  clut; } ;
typedef  enum osd_win_layer { ____Placeholder_osd_win_layer } osd_win_layer ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 size_t OSDWIN_OSD0 ; 
 size_t OSDWIN_OSD1 ; 
#define  PIXFMT_1BPP 130 
#define  PIXFMT_2BPP 129 
#define  PIXFMT_4BPP 128 
 scalar_t__ PIXFMT_OSD_ATTR ; 
 scalar_t__ PIXFMT_RGB888 ; 
 int WIN_OSD0 ; 
 int WIN_OSD1 ; 
 size_t WIN_VID0 ; 
 size_t WIN_VID1 ; 
 int /*<<< orphan*/  _osd_disable_color_key (struct osd_state*,size_t) ; 
 int /*<<< orphan*/  _osd_disable_layer (struct osd_state*,int) ; 
 int /*<<< orphan*/  _osd_disable_vid_rgb888 (struct osd_state*) ; 
 int /*<<< orphan*/  _osd_dm6446_vid0_pingpong (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int /*<<< orphan*/  _osd_enable_color_key (struct osd_state*,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _osd_enable_vid_rgb888 (struct osd_state*,size_t) ; 
 int /*<<< orphan*/  _osd_set_blending_factor (struct osd_state*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_blink_attribute (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_layer_config (struct osd_state*,int,struct osd_layer_config*) ; 
 int /*<<< orphan*/  _osd_set_osd_clut (struct osd_state*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_palette_map (struct osd_state*,int,unsigned char,unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  _osd_set_rec601_attenuation (struct osd_state*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ is_yc_pixfmt (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int try_layer_config (struct osd_state*,int,struct osd_layer_config*) ; 

__attribute__((used)) static int osd_set_layer_config(struct osd_state *sd, enum osd_layer layer,
				struct osd_layer_config *lconfig)
{
	struct osd_state *osd = sd;
	struct osd_window_state *win = &osd->win[layer];
	struct osd_layer_config *cfg = &win->lconfig;
	unsigned long flags;
	int reject_config;

	spin_lock_irqsave(&osd->lock, flags);

	reject_config = try_layer_config(sd, layer, lconfig);
	if (reject_config) {
		spin_unlock_irqrestore(&osd->lock, flags);
		return reject_config;
	}

	/* update the current Cb/Cr order */
	if (is_yc_pixfmt(lconfig->pixfmt))
		osd->yc_pixfmt = lconfig->pixfmt;

	/*
	 * If we are switching OSD1 from normal mode to attribute mode or from
	 * attribute mode to normal mode, then we must disable the window.
	 */
	if (layer == WIN_OSD1) {
		if (((lconfig->pixfmt == PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt != PIXFMT_OSD_ATTR)) ||
		  ((lconfig->pixfmt != PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt == PIXFMT_OSD_ATTR))) {
			win->is_enabled = 0;
			_osd_disable_layer(sd, layer);
		}
	}

	_osd_set_layer_config(sd, layer, lconfig);

	if (layer == WIN_OSD1) {
		struct osd_osdwin_state *osdwin_state =
		    &osd->osdwin[OSDWIN_OSD1];

		if ((lconfig->pixfmt != PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt == PIXFMT_OSD_ATTR)) {
			/*
			 * We just switched OSD1 from attribute mode to normal
			 * mode, so we must initialize the CLUT select, the
			 * blend factor, transparency colorkey enable, and
			 * attenuation enable (DM6446 only) bits in the
			 * OSDWIN1MD register.
			 */
			_osd_set_osd_clut(sd, OSDWIN_OSD1,
						   osdwin_state->clut);
			_osd_set_blending_factor(sd, OSDWIN_OSD1,
							  osdwin_state->blend);
			if (osdwin_state->colorkey_blending) {
				_osd_enable_color_key(sd, OSDWIN_OSD1,
							       osdwin_state->
							       colorkey,
							       lconfig->pixfmt);
			} else
				_osd_disable_color_key(sd, OSDWIN_OSD1);
			_osd_set_rec601_attenuation(sd, OSDWIN_OSD1,
						    osdwin_state->
						    rec601_attenuation);
		} else if ((lconfig->pixfmt == PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt != PIXFMT_OSD_ATTR)) {
			/*
			 * We just switched OSD1 from normal mode to attribute
			 * mode, so we must initialize the blink enable and
			 * blink interval bits in the OSDATRMD register.
			 */
			_osd_set_blink_attribute(sd, osd->is_blinking,
							  osd->blink);
		}
	}

	/*
	 * If we just switched to a 1-, 2-, or 4-bits-per-pixel bitmap format
	 * then configure a default palette map.
	 */
	if ((lconfig->pixfmt != cfg->pixfmt) &&
	  ((lconfig->pixfmt == PIXFMT_1BPP) ||
	  (lconfig->pixfmt == PIXFMT_2BPP) ||
	  (lconfig->pixfmt == PIXFMT_4BPP))) {
		enum osd_win_layer osdwin =
		    ((layer == WIN_OSD0) ? OSDWIN_OSD0 : OSDWIN_OSD1);
		struct osd_osdwin_state *osdwin_state =
		    &osd->osdwin[osdwin];
		unsigned char clut_index;
		unsigned char clut_entries = 0;

		switch (lconfig->pixfmt) {
		case PIXFMT_1BPP:
			clut_entries = 2;
			break;
		case PIXFMT_2BPP:
			clut_entries = 4;
			break;
		case PIXFMT_4BPP:
			clut_entries = 16;
			break;
		default:
			break;
		}
		/*
		 * The default palette map maps the pixel value to the clut
		 * index, i.e. pixel value 0 maps to clut entry 0, pixel value
		 * 1 maps to clut entry 1, etc.
		 */
		for (clut_index = 0; clut_index < 16; clut_index++) {
			osdwin_state->palette_map[clut_index] = clut_index;
			if (clut_index < clut_entries) {
				_osd_set_palette_map(sd, osdwin, clut_index,
						     clut_index,
						     lconfig->pixfmt);
			}
		}
	}

	*cfg = *lconfig;
	/* DM6446: configure the RGB888 enable and window selection */
	if (osd->win[WIN_VID0].lconfig.pixfmt == PIXFMT_RGB888)
		_osd_enable_vid_rgb888(sd, WIN_VID0);
	else if (osd->win[WIN_VID1].lconfig.pixfmt == PIXFMT_RGB888)
		_osd_enable_vid_rgb888(sd, WIN_VID1);
	else
		_osd_disable_vid_rgb888(sd);

	if (layer == WIN_VID0) {
		osd->pingpong =
		    _osd_dm6446_vid0_pingpong(sd, osd->field_inversion,
						       win->fb_base_phys,
						       cfg);
	}

	spin_unlock_irqrestore(&osd->lock, flags);

	return 0;
}