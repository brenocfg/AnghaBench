#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct atmel_hlcdc_crtc {TYPE_2__* event; } ;
struct TYPE_4__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_3__ {TYPE_2__* event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 struct atmel_hlcdc_crtc* drm_crtc_to_atmel_hlcdc_crtc (struct drm_crtc*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 

__attribute__((used)) static void atmel_hlcdc_crtc_atomic_begin(struct drm_crtc *c,
					  struct drm_crtc_state *old_s)
{
	struct atmel_hlcdc_crtc *crtc = drm_crtc_to_atmel_hlcdc_crtc(c);

	if (c->state->event) {
		c->state->event->pipe = drm_crtc_index(c);

		WARN_ON(drm_crtc_vblank_get(c) != 0);

		crtc->event = c->state->event;
		c->state->event = NULL;
	}
}