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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;
struct drm_display_mode {int crtc_htotal; int crtc_hsync_start; int crtc_vblank_start; int flags; } ;
struct drm_device {TYPE_1__* vblank; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_3__ {struct drm_display_mode hwmode; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPEFRAME (unsigned int) ; 
 int /*<<< orphan*/  PIPEFRAMEPIXEL (unsigned int) ; 
 int PIPE_FRAME_HIGH_MASK ; 
 int PIPE_FRAME_HIGH_SHIFT ; 
 int PIPE_FRAME_LOW_SHIFT ; 
 int PIPE_PIXEL_MASK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static u32 i915_get_vblank_counter(struct drm_device *dev, unsigned int pipe)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	i915_reg_t high_frame, low_frame;
	u32 high1, high2, low, pixel, vbl_start, hsync_start, htotal;
	const struct drm_display_mode *mode = &dev->vblank[pipe].hwmode;
	unsigned long irqflags;

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