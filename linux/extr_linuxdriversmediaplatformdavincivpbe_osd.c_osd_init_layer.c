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
struct osd_layer_config {int /*<<< orphan*/  pixfmt; scalar_t__ interlaced; scalar_t__ ypos; scalar_t__ xpos; scalar_t__ ysize; scalar_t__ xsize; scalar_t__ line_length; } ;
struct osd_window_state {scalar_t__ fb_base_phys; void* v_zoom; void* h_zoom; scalar_t__ is_enabled; struct osd_layer_config lconfig; } ;
struct osd_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  yc_pixfmt; int /*<<< orphan*/  blink; int /*<<< orphan*/  is_blinking; struct osd_osdwin_state* osdwin; struct osd_window_state* win; } ;
struct osd_osdwin_state {int /*<<< orphan*/  rec601_attenuation; int /*<<< orphan*/  blend; int /*<<< orphan*/  colorkey_blending; int /*<<< orphan*/  clut; } ;
typedef  enum osd_win_layer { ____Placeholder_osd_win_layer } osd_win_layer ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 int /*<<< orphan*/  BLINK_X1 ; 
 int OSDWIN_OSD0 ; 
 int OSDWIN_OSD1 ; 
 int /*<<< orphan*/  OSD_8_VID_0 ; 
 int /*<<< orphan*/  PIXFMT_8BPP ; 
 int /*<<< orphan*/  RAM_CLUT ; 
#define  WIN_OSD0 131 
#define  WIN_OSD1 130 
#define  WIN_VID0 129 
#define  WIN_VID1 128 
 void* ZOOM_X1 ; 
 int /*<<< orphan*/  _osd_disable_color_key (struct osd_state*,int) ; 
 int /*<<< orphan*/  _osd_disable_layer (struct osd_state*,int) ; 
 int /*<<< orphan*/  _osd_set_blending_factor (struct osd_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_layer_config (struct osd_state*,int,struct osd_layer_config*) ; 
 int /*<<< orphan*/  _osd_set_osd_clut (struct osd_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_rec601_attenuation (struct osd_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_zoom (struct osd_state*,int,void*,void*) ; 
 int /*<<< orphan*/  _osd_start_layer (struct osd_state*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void osd_init_layer(struct osd_state *sd, enum osd_layer layer)
{
	struct osd_state *osd = sd;
	struct osd_window_state *win = &osd->win[layer];
	enum osd_win_layer osdwin;
	struct osd_osdwin_state *osdwin_state;
	struct osd_layer_config *cfg = &win->lconfig;
	unsigned long flags;

	spin_lock_irqsave(&osd->lock, flags);

	win->is_enabled = 0;
	_osd_disable_layer(sd, layer);

	win->h_zoom = ZOOM_X1;
	win->v_zoom = ZOOM_X1;
	_osd_set_zoom(sd, layer, win->h_zoom, win->v_zoom);

	win->fb_base_phys = 0;
	_osd_start_layer(sd, layer, win->fb_base_phys, 0);

	cfg->line_length = 0;
	cfg->xsize = 0;
	cfg->ysize = 0;
	cfg->xpos = 0;
	cfg->ypos = 0;
	cfg->interlaced = 0;
	switch (layer) {
	case WIN_OSD0:
	case WIN_OSD1:
		osdwin = (layer == WIN_OSD0) ? OSDWIN_OSD0 : OSDWIN_OSD1;
		osdwin_state = &osd->osdwin[osdwin];
		/*
		 * Other code relies on the fact that OSD windows default to a
		 * bitmap pixel format when they are deallocated, so don't
		 * change this default pixel format.
		 */
		cfg->pixfmt = PIXFMT_8BPP;
		_osd_set_layer_config(sd, layer, cfg);
		osdwin_state->clut = RAM_CLUT;
		_osd_set_osd_clut(sd, osdwin, osdwin_state->clut);
		osdwin_state->colorkey_blending = 0;
		_osd_disable_color_key(sd, osdwin);
		osdwin_state->blend = OSD_8_VID_0;
		_osd_set_blending_factor(sd, osdwin, osdwin_state->blend);
		osdwin_state->rec601_attenuation = 0;
		_osd_set_rec601_attenuation(sd, osdwin,
						     osdwin_state->
						     rec601_attenuation);
		if (osdwin == OSDWIN_OSD1) {
			osd->is_blinking = 0;
			osd->blink = BLINK_X1;
		}
		break;
	case WIN_VID0:
	case WIN_VID1:
		cfg->pixfmt = osd->yc_pixfmt;
		_osd_set_layer_config(sd, layer, cfg);
		break;
	}

	spin_unlock_irqrestore(&osd->lock, flags);
}