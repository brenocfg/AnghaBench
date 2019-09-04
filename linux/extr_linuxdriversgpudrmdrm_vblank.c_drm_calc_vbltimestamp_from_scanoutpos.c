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
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {int tv_nsec; scalar_t__ tv_sec; } ;
struct drm_display_mode {scalar_t__ crtc_clock; int crtc_htotal; } ;
struct drm_vblank_crtc {struct drm_display_mode hwmode; } ;
struct drm_device {unsigned int num_crtcs; TYPE_1__* driver; struct drm_vblank_crtc* vblank; } ;
struct drm_crtc {struct drm_display_mode hwmode; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int (* get_scanout_position ) (struct drm_device*,unsigned int,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_display_mode const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_VBL (char*,unsigned int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int DRM_TIMESTAMP_MAXRETRIES ; 
 int DRM_UT_VBL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (scalar_t__) ; 
 int div_s64 (long long,scalar_t__) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_crtc_from_index (struct drm_device*,unsigned int) ; 
 int drm_debug ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_device*,unsigned int,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 

bool drm_calc_vbltimestamp_from_scanoutpos(struct drm_device *dev,
					   unsigned int pipe,
					   int *max_error,
					   ktime_t *vblank_time,
					   bool in_vblank_irq)
{
	struct timespec64 ts_etime, ts_vblank_time;
	ktime_t stime, etime;
	bool vbl_status;
	struct drm_crtc *crtc;
	const struct drm_display_mode *mode;
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	int vpos, hpos, i;
	int delta_ns, duration_ns;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return false;

	crtc = drm_crtc_from_index(dev, pipe);

	if (pipe >= dev->num_crtcs || !crtc) {
		DRM_ERROR("Invalid crtc %u\n", pipe);
		return false;
	}

	/* Scanout position query not supported? Should not happen. */
	if (!dev->driver->get_scanout_position) {
		DRM_ERROR("Called from driver w/o get_scanout_position()!?\n");
		return false;
	}

	if (drm_drv_uses_atomic_modeset(dev))
		mode = &vblank->hwmode;
	else
		mode = &crtc->hwmode;

	/* If mode timing undefined, just return as no-op:
	 * Happens during initial modesetting of a crtc.
	 */
	if (mode->crtc_clock == 0) {
		DRM_DEBUG("crtc %u: Noop due to uninitialized mode.\n", pipe);
		WARN_ON_ONCE(drm_drv_uses_atomic_modeset(dev));

		return false;
	}

	/* Get current scanout position with system timestamp.
	 * Repeat query up to DRM_TIMESTAMP_MAXRETRIES times
	 * if single query takes longer than max_error nanoseconds.
	 *
	 * This guarantees a tight bound on maximum error if
	 * code gets preempted or delayed for some reason.
	 */
	for (i = 0; i < DRM_TIMESTAMP_MAXRETRIES; i++) {
		/*
		 * Get vertical and horizontal scanout position vpos, hpos,
		 * and bounding timestamps stime, etime, pre/post query.
		 */
		vbl_status = dev->driver->get_scanout_position(dev, pipe,
							       in_vblank_irq,
							       &vpos, &hpos,
							       &stime, &etime,
							       mode);

		/* Return as no-op if scanout query unsupported or failed. */
		if (!vbl_status) {
			DRM_DEBUG("crtc %u : scanoutpos query failed.\n",
				  pipe);
			return false;
		}

		/* Compute uncertainty in timestamp of scanout position query. */
		duration_ns = ktime_to_ns(etime) - ktime_to_ns(stime);

		/* Accept result with <  max_error nsecs timing uncertainty. */
		if (duration_ns <= *max_error)
			break;
	}

	/* Noisy system timing? */
	if (i == DRM_TIMESTAMP_MAXRETRIES) {
		DRM_DEBUG("crtc %u: Noisy timestamp %d us > %d us [%d reps].\n",
			  pipe, duration_ns/1000, *max_error/1000, i);
	}

	/* Return upper bound of timestamp precision error. */
	*max_error = duration_ns;

	/* Convert scanout position into elapsed time at raw_time query
	 * since start of scanout at first display scanline. delta_ns
	 * can be negative if start of scanout hasn't happened yet.
	 */
	delta_ns = div_s64(1000000LL * (vpos * mode->crtc_htotal + hpos),
			   mode->crtc_clock);

	/* Subtract time delta from raw timestamp to get final
	 * vblank_time timestamp for end of vblank.
	 */
	*vblank_time = ktime_sub_ns(etime, delta_ns);

	if ((drm_debug & DRM_UT_VBL) == 0)
		return true;

	ts_etime = ktime_to_timespec64(etime);
	ts_vblank_time = ktime_to_timespec64(*vblank_time);

	DRM_DEBUG_VBL("crtc %u : v p(%d,%d)@ %lld.%06ld -> %lld.%06ld [e %d us, %d rep]\n",
		      pipe, hpos, vpos,
		      (u64)ts_etime.tv_sec, ts_etime.tv_nsec / 1000,
		      (u64)ts_vblank_time.tv_sec, ts_vblank_time.tv_nsec / 1000,
		      duration_ns / 1000, i);

	return true;
}