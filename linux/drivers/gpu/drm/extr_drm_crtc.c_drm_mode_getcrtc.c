#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct drm_plane {int /*<<< orphan*/  mutex; TYPE_5__* state; TYPE_4__* fb; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct drm_mode_crtc {int x; int y; int mode_valid; TYPE_7__ mode; scalar_t__ fb_id; int /*<<< orphan*/  gamma_size; int /*<<< orphan*/  crtc_id; } ;
struct drm_file {int /*<<< orphan*/  aspect_ratio_allowed; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int x; int y; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mode; scalar_t__ enabled; TYPE_6__* state; int /*<<< orphan*/  gamma_size; struct drm_plane* primary; } ;
struct TYPE_13__ {int /*<<< orphan*/  mode; scalar_t__ enable; } ;
struct TYPE_12__ {int src_x; int src_y; TYPE_2__* fb; } ;
struct TYPE_10__ {scalar_t__ id; } ;
struct TYPE_11__ {TYPE_3__ base; } ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_9__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PIC_AR_MASK ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_crtc_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_convert_to_umode (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 

int drm_mode_getcrtc(struct drm_device *dev,
		     void *data, struct drm_file *file_priv)
{
	struct drm_mode_crtc *crtc_resp = data;
	struct drm_crtc *crtc;
	struct drm_plane *plane;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	crtc = drm_crtc_find(dev, file_priv, crtc_resp->crtc_id);
	if (!crtc)
		return -ENOENT;

	plane = crtc->primary;

	crtc_resp->gamma_size = crtc->gamma_size;

	drm_modeset_lock(&plane->mutex, NULL);
	if (plane->state && plane->state->fb)
		crtc_resp->fb_id = plane->state->fb->base.id;
	else if (!plane->state && plane->fb)
		crtc_resp->fb_id = plane->fb->base.id;
	else
		crtc_resp->fb_id = 0;

	if (plane->state) {
		crtc_resp->x = plane->state->src_x >> 16;
		crtc_resp->y = plane->state->src_y >> 16;
	}
	drm_modeset_unlock(&plane->mutex);

	drm_modeset_lock(&crtc->mutex, NULL);
	if (crtc->state) {
		if (crtc->state->enable) {
			drm_mode_convert_to_umode(&crtc_resp->mode, &crtc->state->mode);
			crtc_resp->mode_valid = 1;
		} else {
			crtc_resp->mode_valid = 0;
		}
	} else {
		crtc_resp->x = crtc->x;
		crtc_resp->y = crtc->y;

		if (crtc->enabled) {
			drm_mode_convert_to_umode(&crtc_resp->mode, &crtc->mode);
			crtc_resp->mode_valid = 1;

		} else {
			crtc_resp->mode_valid = 0;
		}
	}
	if (!file_priv->aspect_ratio_allowed)
		crtc_resp->mode.flags &= ~DRM_MODE_FLAG_PIC_AR_MASK;
	drm_modeset_unlock(&crtc->mutex);

	return 0;
}