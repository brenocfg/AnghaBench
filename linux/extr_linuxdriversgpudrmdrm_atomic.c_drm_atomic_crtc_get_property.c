#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_property {int dummy; } ;
struct drm_mode_config {struct drm_property* prop_out_fence_ptr; struct drm_property* gamma_lut_property; struct drm_property* ctm_property; struct drm_property* degamma_lut_property; struct drm_property* prop_mode_id; struct drm_property* prop_active; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct drm_crtc_state {TYPE_8__* gamma_lut; TYPE_6__* ctm; TYPE_4__* degamma_lut; TYPE_2__* mode_blob; int /*<<< orphan*/  active; } ;
struct drm_crtc {TYPE_9__* funcs; struct drm_device* dev; } ;
struct TYPE_18__ {int (* atomic_get_property ) (struct drm_crtc*,struct drm_crtc_state const*,struct drm_property*,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {TYPE_7__ base; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_15__ {TYPE_5__ base; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_3__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct drm_crtc*,struct drm_crtc_state const*,struct drm_property*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
drm_atomic_crtc_get_property(struct drm_crtc *crtc,
		const struct drm_crtc_state *state,
		struct drm_property *property, uint64_t *val)
{
	struct drm_device *dev = crtc->dev;
	struct drm_mode_config *config = &dev->mode_config;

	if (property == config->prop_active)
		*val = state->active;
	else if (property == config->prop_mode_id)
		*val = (state->mode_blob) ? state->mode_blob->base.id : 0;
	else if (property == config->degamma_lut_property)
		*val = (state->degamma_lut) ? state->degamma_lut->base.id : 0;
	else if (property == config->ctm_property)
		*val = (state->ctm) ? state->ctm->base.id : 0;
	else if (property == config->gamma_lut_property)
		*val = (state->gamma_lut) ? state->gamma_lut->base.id : 0;
	else if (property == config->prop_out_fence_ptr)
		*val = 0;
	else if (crtc->funcs->atomic_get_property)
		return crtc->funcs->atomic_get_property(crtc, state, property, val);
	else
		return -EINVAL;

	return 0;
}