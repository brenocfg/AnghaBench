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
typedef  int u64 ;
struct drm_display_mode {int crtc_clock; int crtc_htotal; int crtc_vtotal; int flags; int crtc_vdisplay; } ;
struct drm_vblank_crtc {int linedur_ns; int framedur_ns; struct drm_display_mode hwmode; } ;
struct drm_device {unsigned int num_crtcs; struct drm_vblank_crtc* vblank; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ WARN_ON (int) ; 
 int div_u64 (int,int) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 

void drm_calc_timestamping_constants(struct drm_crtc *crtc,
				     const struct drm_display_mode *mode)
{
	struct drm_device *dev = crtc->dev;
	unsigned int pipe = drm_crtc_index(crtc);
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	int linedur_ns = 0, framedur_ns = 0;
	int dotclock = mode->crtc_clock;

	if (!dev->num_crtcs)
		return;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	/* Valid dotclock? */
	if (dotclock > 0) {
		int frame_size = mode->crtc_htotal * mode->crtc_vtotal;

		/*
		 * Convert scanline length in pixels and video
		 * dot clock to line duration and frame duration
		 * in nanoseconds:
		 */
		linedur_ns  = div_u64((u64) mode->crtc_htotal * 1000000, dotclock);
		framedur_ns = div_u64((u64) frame_size * 1000000, dotclock);

		/*
		 * Fields of interlaced scanout modes are only half a frame duration.
		 */
		if (mode->flags & DRM_MODE_FLAG_INTERLACE)
			framedur_ns /= 2;
	} else
		DRM_ERROR("crtc %u: Can't calculate constants, dotclock = 0!\n",
			  crtc->base.id);

	vblank->linedur_ns  = linedur_ns;
	vblank->framedur_ns = framedur_ns;
	vblank->hwmode = *mode;

	DRM_DEBUG("crtc %u: hwmode: htotal %d, vtotal %d, vdisplay %d\n",
		  crtc->base.id, mode->crtc_htotal,
		  mode->crtc_vtotal, mode->crtc_vdisplay);
	DRM_DEBUG("crtc %u: clock %d kHz framedur %d linedur %d\n",
		  crtc->base.id, dotclock, framedur_ns, linedur_ns);
}