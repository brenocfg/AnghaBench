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
struct osd_layer_config {int dummy; } ;
struct osd_window_state {unsigned long fb_base_phys; struct osd_layer_config lconfig; } ;
struct osd_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  field_inversion; int /*<<< orphan*/  pingpong; struct osd_window_state* win; } ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 int WIN_VID0 ; 
 int /*<<< orphan*/  _osd_dm6446_vid0_pingpong (struct osd_state*,int /*<<< orphan*/ ,unsigned long,struct osd_layer_config*) ; 
 int /*<<< orphan*/  _osd_start_layer (struct osd_state*,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void osd_start_layer(struct osd_state *sd, enum osd_layer layer,
			    unsigned long fb_base_phys,
			    unsigned long cbcr_ofst)
{
	struct osd_state *osd = sd;
	struct osd_window_state *win = &osd->win[layer];
	struct osd_layer_config *cfg = &win->lconfig;
	unsigned long flags;

	spin_lock_irqsave(&osd->lock, flags);

	win->fb_base_phys = fb_base_phys & ~0x1F;
	_osd_start_layer(sd, layer, fb_base_phys, cbcr_ofst);

	if (layer == WIN_VID0) {
		osd->pingpong =
		    _osd_dm6446_vid0_pingpong(sd, osd->field_inversion,
						       win->fb_base_phys,
						       cfg);
	}

	spin_unlock_irqrestore(&osd->lock, flags);
}