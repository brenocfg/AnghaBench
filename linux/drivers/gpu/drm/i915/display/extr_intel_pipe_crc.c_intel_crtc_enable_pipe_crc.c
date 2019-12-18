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
typedef  int /*<<< orphan*/  u32 ;
struct intel_pipe_crc {scalar_t__ skipped; int /*<<< orphan*/  source; } ;
struct TYPE_2__ {int /*<<< orphan*/  opened; } ;
struct drm_crtc {size_t index; TYPE_1__ crc; int /*<<< orphan*/  dev; } ;
struct intel_crtc {struct drm_crtc base; } ;
struct drm_i915_private {struct intel_pipe_crc* pipe_crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CRC_CTL (size_t) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ get_new_crc_ctl_reg (struct drm_i915_private*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_crtc_enable_pipe_crc(struct intel_crtc *intel_crtc)
{
	struct drm_crtc *crtc = &intel_crtc->base;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_pipe_crc *pipe_crc = &dev_priv->pipe_crc[crtc->index];
	u32 val = 0;

	if (!crtc->crc.opened)
		return;

	if (get_new_crc_ctl_reg(dev_priv, crtc->index, &pipe_crc->source, &val) < 0)
		return;

	/* Don't need pipe_crc->lock here, IRQs are not generated. */
	pipe_crc->skipped = 0;

	I915_WRITE(PIPE_CRC_CTL(crtc->index), val);
	POSTING_READ(PIPE_CRC_CTL(crtc->index));
}