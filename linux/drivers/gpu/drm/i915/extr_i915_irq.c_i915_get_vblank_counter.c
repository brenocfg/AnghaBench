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
struct drm_display_mode {int crtc_htotal; int crtc_hsync_start; int crtc_vblank_start; int flags; } ;
struct drm_vblank_crtc {int /*<<< orphan*/  max_vblank_count; struct drm_display_mode hwmode; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct drm_vblank_crtc* vblank; } ;
struct drm_i915_private {TYPE_2__ uncore; TYPE_1__ drm; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_6__ {int pipe; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPEFRAME (int) ; 
 int /*<<< orphan*/  PIPEFRAMEPIXEL (int) ; 
 int PIPE_FRAME_HIGH_MASK ; 
 int PIPE_FRAME_HIGH_SHIFT ; 
 int PIPE_FRAME_LOW_SHIFT ; 
 int PIPE_PIXEL_MASK ; 
 size_t drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_crtc (struct drm_crtc*) ; 

u32 i915_get_vblank_counter(struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct drm_vblank_crtc *vblank = &dev_priv->drm.vblank[drm_crtc_index(crtc)];
	const struct drm_display_mode *mode = &vblank->hwmode;
	enum pipe pipe = to_intel_crtc(crtc)->pipe;
	i915_reg_t high_frame, low_frame;
	u32 high1, high2, low, pixel, vbl_start, hsync_start, htotal;
	unsigned long irqflags;

	/*
	 * On i965gm TV output the frame counter only works up to
	 * the point when we enable the TV encoder. After that the
	 * frame counter ceases to work and reads zero. We need a
	 * vblank wait before enabling the TV encoder and so we
	 * have to enable vblank interrupts while the frame counter
	 * is still in a working state. However the core vblank code
	 * does not like us returning non-zero frame counter values
	 * when we've told it that we don't have a working frame
	 * counter. Thus we must stop non-zero values leaking out.
	 */
	if (!vblank->max_vblank_count)
		return 0;

	htotal = mode->crtc_htotal;
	hsync_start = mode->crtc_hsync_start;
	vbl_start = mode->crtc_vblank_start;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		vbl_start = DIV_ROUND_UP(vbl_start, 2);

	/* Convert to pixel count */
	vbl_start *= htotal;

	/* Start of vblank event occurs at start of hsync */
	vbl_start -= htotal - hsync_start;

	high_frame = PIPEFRAME(pipe);
	low_frame = PIPEFRAMEPIXEL(pipe);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/*
	 * High & low register fields aren't synchronized, so make sure
	 * we get a low value that's stable across two reads of the high
	 * register.
	 */
	do {
		high1 = I915_READ_FW(high_frame) & PIPE_FRAME_HIGH_MASK;
		low   = I915_READ_FW(low_frame);
		high2 = I915_READ_FW(high_frame) & PIPE_FRAME_HIGH_MASK;
	} while (high1 != high2);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);

	high1 >>= PIPE_FRAME_HIGH_SHIFT;
	pixel = low & PIPE_PIXEL_MASK;
	low >>= PIPE_FRAME_LOW_SHIFT;

	/*
	 * The frame counter increments at beginning of active.
	 * Cook up a vblank counter by also checking the pixel
	 * counter against vblank start.
	 */
	return (((high1 << 8) | low) + (pixel >= vbl_start)) & 0xffffff;
}