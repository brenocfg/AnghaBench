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
struct osd_layer_config {scalar_t__ pixfmt; int /*<<< orphan*/  ysize; int /*<<< orphan*/  xsize; int /*<<< orphan*/  line_length; } ;
struct osd_window_state {int is_enabled; int /*<<< orphan*/  fb_base_phys; int /*<<< orphan*/  is_allocated; struct osd_layer_config lconfig; } ;
struct osd_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  blink; int /*<<< orphan*/  is_blinking; struct osd_window_state* win; } ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 scalar_t__ PIXFMT_OSD_ATTR ; 
 int /*<<< orphan*/  _osd_enable_attribute_mode (struct osd_state*) ; 
 int /*<<< orphan*/  _osd_enable_layer (struct osd_state*,int) ; 
 int /*<<< orphan*/  _osd_set_blink_attribute (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int osd_enable_layer(struct osd_state *sd, enum osd_layer layer,
			    int otherwin)
{
	struct osd_state *osd = sd;
	struct osd_window_state *win = &osd->win[layer];
	struct osd_layer_config *cfg = &win->lconfig;
	unsigned long flags;

	spin_lock_irqsave(&osd->lock, flags);

	/*
	 * use otherwin flag to know this is the other vid window
	 * in YUV420 mode, if is, skip this check
	 */
	if (!otherwin && (!win->is_allocated ||
			!win->fb_base_phys ||
			!cfg->line_length ||
			!cfg->xsize ||
			!cfg->ysize)) {
		spin_unlock_irqrestore(&osd->lock, flags);
		return -1;
	}

	if (win->is_enabled) {
		spin_unlock_irqrestore(&osd->lock, flags);
		return 0;
	}
	win->is_enabled = 1;

	if (cfg->pixfmt != PIXFMT_OSD_ATTR)
		_osd_enable_layer(sd, layer);
	else {
		_osd_enable_attribute_mode(sd);
		_osd_set_blink_attribute(sd, osd->is_blinking, osd->blink);
	}

	spin_unlock_irqrestore(&osd->lock, flags);

	return 0;
}