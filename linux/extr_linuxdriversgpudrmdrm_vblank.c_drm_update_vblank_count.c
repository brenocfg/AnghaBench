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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct drm_vblank_crtc {int framedur_ns; scalar_t__ last; int inmodeset; int /*<<< orphan*/  count; int /*<<< orphan*/  time; } ;
struct drm_device {scalar_t__ max_vblank_count; struct drm_vblank_crtc* vblank; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST_ULL (scalar_t__,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_VBL (char*,unsigned int,long long,...) ; 
 int DRM_TIMESTAMP_MAXRETRIES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ __get_vblank_counter (struct drm_device*,unsigned int) ; 
 int drm_get_last_vbltimestamp (struct drm_device*,unsigned int,scalar_t__*,int) ; 
 int /*<<< orphan*/  ktime_sub (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_vblank (struct drm_device*,unsigned int,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void drm_update_vblank_count(struct drm_device *dev, unsigned int pipe,
				    bool in_vblank_irq)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	u32 cur_vblank, diff;
	bool rc;
	ktime_t t_vblank;
	int count = DRM_TIMESTAMP_MAXRETRIES;
	int framedur_ns = vblank->framedur_ns;

	/*
	 * Interrupts were disabled prior to this call, so deal with counter
	 * wrap if needed.
	 * NOTE!  It's possible we lost a full dev->max_vblank_count + 1 events
	 * here if the register is small or we had vblank interrupts off for
	 * a long time.
	 *
	 * We repeat the hardware vblank counter & timestamp query until
	 * we get consistent results. This to prevent races between gpu
	 * updating its hardware counter while we are retrieving the
	 * corresponding vblank timestamp.
	 */
	do {
		cur_vblank = __get_vblank_counter(dev, pipe);
		rc = drm_get_last_vbltimestamp(dev, pipe, &t_vblank, in_vblank_irq);
	} while (cur_vblank != __get_vblank_counter(dev, pipe) && --count > 0);

	if (dev->max_vblank_count != 0) {
		/* trust the hw counter when it's around */
		diff = (cur_vblank - vblank->last) & dev->max_vblank_count;
	} else if (rc && framedur_ns) {
		u64 diff_ns = ktime_to_ns(ktime_sub(t_vblank, vblank->time));

		/*
		 * Figure out how many vblanks we've missed based
		 * on the difference in the timestamps and the
		 * frame/field duration.
		 */
		diff = DIV_ROUND_CLOSEST_ULL(diff_ns, framedur_ns);

		if (diff == 0 && in_vblank_irq)
			DRM_DEBUG_VBL("crtc %u: Redundant vblirq ignored."
				      " diff_ns = %lld, framedur_ns = %d)\n",
				      pipe, (long long) diff_ns, framedur_ns);
	} else {
		/* some kind of default for drivers w/o accurate vbl timestamping */
		diff = in_vblank_irq ? 1 : 0;
	}

	/*
	 * Within a drm_vblank_pre_modeset - drm_vblank_post_modeset
	 * interval? If so then vblank irqs keep running and it will likely
	 * happen that the hardware vblank counter is not trustworthy as it
	 * might reset at some point in that interval and vblank timestamps
	 * are not trustworthy either in that interval. Iow. this can result
	 * in a bogus diff >> 1 which must be avoided as it would cause
	 * random large forward jumps of the software vblank counter.
	 */
	if (diff > 1 && (vblank->inmodeset & 0x2)) {
		DRM_DEBUG_VBL("clamping vblank bump to 1 on crtc %u: diffr=%u"
			      " due to pre-modeset.\n", pipe, diff);
		diff = 1;
	}

	DRM_DEBUG_VBL("updating vblank count on crtc %u:"
		      " current=%llu, diff=%u, hw=%u hw_last=%u\n",
		      pipe, vblank->count, diff, cur_vblank, vblank->last);

	if (diff == 0) {
		WARN_ON_ONCE(cur_vblank != vblank->last);
		return;
	}

	/*
	 * Only reinitialize corresponding vblank timestamp if high-precision query
	 * available and didn't fail, or we were called from the vblank interrupt.
	 * Otherwise reinitialize delayed at next vblank interrupt and assign 0
	 * for now, to mark the vblanktimestamp as invalid.
	 */
	if (!rc && !in_vblank_irq)
		t_vblank = 0;

	store_vblank(dev, pipe, diff, t_vblank, cur_vblank);
}