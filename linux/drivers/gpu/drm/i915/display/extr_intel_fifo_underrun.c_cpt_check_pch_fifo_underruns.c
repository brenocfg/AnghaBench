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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERR_INT ; 
 int SERR_INT_TRANS_FIFO_UNDERRUN (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_pch_fifo_underrun (struct drm_i915_private*,int) ; 

__attribute__((used)) static void cpt_check_pch_fifo_underruns(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pch_transcoder = crtc->pipe;
	u32 serr_int = I915_READ(SERR_INT);

	lockdep_assert_held(&dev_priv->irq_lock);

	if ((serr_int & SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder)) == 0)
		return;

	I915_WRITE(SERR_INT, SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder));
	POSTING_READ(SERR_INT);

	trace_intel_pch_fifo_underrun(dev_priv, pch_transcoder);
	DRM_ERROR("pch fifo underrun on pch transcoder %c\n",
		  pipe_name(pch_transcoder));
}