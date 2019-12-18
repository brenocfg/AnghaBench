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
struct drm_vblank_crtc {int /*<<< orphan*/  enabled; } ;
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ vblank_disable_immediate; struct drm_vblank_crtc* vblank; int /*<<< orphan*/  irq_enabled; } ;
struct drm_crtc_get_sequence {int /*<<< orphan*/  sequence_ns; int /*<<< orphan*/  sequence; int /*<<< orphan*/  active; int /*<<< orphan*/  crtc_id; } ;
struct drm_crtc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  enabled; TYPE_1__* state; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_crtc_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int drm_crtc_index (struct drm_crtc*) ; 
 int drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_vblank_count_and_time (struct drm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 

int drm_crtc_get_sequence_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_priv)
{
	struct drm_crtc *crtc;
	struct drm_vblank_crtc *vblank;
	int pipe;
	struct drm_crtc_get_sequence *get_seq = data;
	ktime_t now;
	bool vblank_enabled;
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	if (!dev->irq_enabled)
		return -EINVAL;

	crtc = drm_crtc_find(dev, file_priv, get_seq->crtc_id);
	if (!crtc)
		return -ENOENT;

	pipe = drm_crtc_index(crtc);

	vblank = &dev->vblank[pipe];
	vblank_enabled = dev->vblank_disable_immediate && READ_ONCE(vblank->enabled);

	if (!vblank_enabled) {
		ret = drm_crtc_vblank_get(crtc);
		if (ret) {
			DRM_DEBUG("crtc %d failed to acquire vblank counter, %d\n", pipe, ret);
			return ret;
		}
	}
	drm_modeset_lock(&crtc->mutex, NULL);
	if (crtc->state)
		get_seq->active = crtc->state->enable;
	else
		get_seq->active = crtc->enabled;
	drm_modeset_unlock(&crtc->mutex);
	get_seq->sequence = drm_vblank_count_and_time(dev, pipe, &now);
	get_seq->sequence_ns = ktime_to_ns(now);
	if (!vblank_enabled)
		drm_crtc_vblank_put(crtc);
	return 0;
}