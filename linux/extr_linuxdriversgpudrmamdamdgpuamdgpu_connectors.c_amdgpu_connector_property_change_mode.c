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
struct drm_encoder {struct drm_crtc* crtc; } ;
struct drm_crtc {TYPE_1__* primary; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  mode; scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_helper_set_mode (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_connector_property_change_mode(struct drm_encoder *encoder)
{
	struct drm_crtc *crtc = encoder->crtc;

	if (crtc && crtc->enabled) {
		drm_crtc_helper_set_mode(crtc, &crtc->mode,
					 crtc->x, crtc->y, crtc->primary->fb);
	}
}