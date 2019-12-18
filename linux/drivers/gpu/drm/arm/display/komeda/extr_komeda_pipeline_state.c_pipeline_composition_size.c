#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct komeda_crtc_state {TYPE_1__ base; } ;

/* Variables and functions */

void pipeline_composition_size(struct komeda_crtc_state *kcrtc_st,
			       u16 *hsize, u16 *vsize)
{
	struct drm_display_mode *m = &kcrtc_st->base.adjusted_mode;

	if (hsize)
		*hsize = m->hdisplay;
	if (vsize)
		*vsize = m->vdisplay;
}