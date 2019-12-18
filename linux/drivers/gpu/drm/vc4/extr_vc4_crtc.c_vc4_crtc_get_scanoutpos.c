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
typedef  int /*<<< orphan*/  u32 ;
struct vc4_dev {int dummy; } ;
struct vc4_crtc {int cob_size; int /*<<< orphan*/  t_vblank; int /*<<< orphan*/  channel; } ;
struct drm_display_mode {int flags; int crtc_htotal; int crtc_hdisplay; int vtotal; int vdisplay; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_DISPSTATX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_DISPSTATX_FRAME_COUNT ; 
 int /*<<< orphan*/  SCALER_DISPSTATX_LINE ; 
 int VC4_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_crtc_from_index (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

bool vc4_crtc_get_scanoutpos(struct drm_device *dev, unsigned int crtc_id,
			     bool in_vblank_irq, int *vpos, int *hpos,
			     ktime_t *stime, ktime_t *etime,
			     const struct drm_display_mode *mode)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct drm_crtc *crtc = drm_crtc_from_index(dev, crtc_id);
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	u32 val;
	int fifo_lines;
	int vblank_lines;
	bool ret = false;

	/* preempt_disable_rt() should go right here in PREEMPT_RT patchset. */

	/* Get optional system timestamp before query. */
	if (stime)
		*stime = ktime_get();

	/*
	 * Read vertical scanline which is currently composed for our
	 * pixelvalve by the HVS, and also the scaler status.
	 */
	val = HVS_READ(SCALER_DISPSTATX(vc4_crtc->channel));

	/* Get optional system timestamp after query. */
	if (etime)
		*etime = ktime_get();

	/* preempt_enable_rt() should go right here in PREEMPT_RT patchset. */

	/* Vertical position of hvs composed scanline. */
	*vpos = VC4_GET_FIELD(val, SCALER_DISPSTATX_LINE);
	*hpos = 0;

	if (mode->flags & DRM_MODE_FLAG_INTERLACE) {
		*vpos /= 2;

		/* Use hpos to correct for field offset in interlaced mode. */
		if (VC4_GET_FIELD(val, SCALER_DISPSTATX_FRAME_COUNT) % 2)
			*hpos += mode->crtc_htotal / 2;
	}

	/* This is the offset we need for translating hvs -> pv scanout pos. */
	fifo_lines = vc4_crtc->cob_size / mode->crtc_hdisplay;

	if (fifo_lines > 0)
		ret = true;

	/* HVS more than fifo_lines into frame for compositing? */
	if (*vpos > fifo_lines) {
		/*
		 * We are in active scanout and can get some meaningful results
		 * from HVS. The actual PV scanout can not trail behind more
		 * than fifo_lines as that is the fifo's capacity. Assume that
		 * in active scanout the HVS and PV work in lockstep wrt. HVS
		 * refilling the fifo and PV consuming from the fifo, ie.
		 * whenever the PV consumes and frees up a scanline in the
		 * fifo, the HVS will immediately refill it, therefore
		 * incrementing vpos. Therefore we choose HVS read position -
		 * fifo size in scanlines as a estimate of the real scanout
		 * position of the PV.
		 */
		*vpos -= fifo_lines + 1;

		return ret;
	}

	/*
	 * Less: This happens when we are in vblank and the HVS, after getting
	 * the VSTART restart signal from the PV, just started refilling its
	 * fifo with new lines from the top-most lines of the new framebuffers.
	 * The PV does not scan out in vblank, so does not remove lines from
	 * the fifo, so the fifo will be full quickly and the HVS has to pause.
	 * We can't get meaningful readings wrt. scanline position of the PV
	 * and need to make things up in a approximative but consistent way.
	 */
	vblank_lines = mode->vtotal - mode->vdisplay;

	if (in_vblank_irq) {
		/*
		 * Assume the irq handler got called close to first
		 * line of vblank, so PV has about a full vblank
		 * scanlines to go, and as a base timestamp use the
		 * one taken at entry into vblank irq handler, so it
		 * is not affected by random delays due to lock
		 * contention on event_lock or vblank_time lock in
		 * the core.
		 */
		*vpos = -vblank_lines;

		if (stime)
			*stime = vc4_crtc->t_vblank;
		if (etime)
			*etime = vc4_crtc->t_vblank;

		/*
		 * If the HVS fifo is not yet full then we know for certain
		 * we are at the very beginning of vblank, as the hvs just
		 * started refilling, and the stime and etime timestamps
		 * truly correspond to start of vblank.
		 *
		 * Unfortunately there's no way to report this to upper levels
		 * and make it more useful.
		 */
	} else {
		/*
		 * No clue where we are inside vblank. Return a vpos of zero,
		 * which will cause calling code to just return the etime
		 * timestamp uncorrected. At least this is no worse than the
		 * standard fallback.
		 */
		*vpos = 0;
	}

	return ret;
}