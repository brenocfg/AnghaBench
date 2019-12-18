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
typedef  int u32 ;
struct drm_crtc {TYPE_3__* state; } ;
struct drm_color_lut {int red; int green; int blue; } ;
struct TYPE_4__ {struct drm_crtc* crtc; } ;
struct atmel_hlcdc_plane_state {TYPE_1__ base; } ;
struct atmel_hlcdc_plane {int /*<<< orphan*/  layer; } ;
struct TYPE_6__ {TYPE_2__* gamma_lut; int /*<<< orphan*/  color_mgmt_changed; } ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int ATMEL_HLCDC_CLUT_SIZE ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_write_clut (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void atmel_hlcdc_plane_update_clut(struct atmel_hlcdc_plane *plane,
					  struct atmel_hlcdc_plane_state *state)
{
	struct drm_crtc *crtc = state->base.crtc;
	struct drm_color_lut *lut;
	int idx;

	if (!crtc || !crtc->state)
		return;

	if (!crtc->state->color_mgmt_changed || !crtc->state->gamma_lut)
		return;

	lut = (struct drm_color_lut *)crtc->state->gamma_lut->data;

	for (idx = 0; idx < ATMEL_HLCDC_CLUT_SIZE; idx++, lut++) {
		u32 val = ((lut->red << 8) & 0xff0000) |
			(lut->green & 0xff00) |
			(lut->blue >> 8);

		atmel_hlcdc_layer_write_clut(&plane->layer, idx, val);
	}
}