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
struct intel_link_m_n {int link_m; int link_n; int gmch_m; int gmch_n; int tu; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_TRANS_DATA_M1 (int) ; 
 int /*<<< orphan*/  PCH_TRANS_DATA_N1 (int) ; 
 int /*<<< orphan*/  PCH_TRANS_LINK_M1 (int) ; 
 int /*<<< orphan*/  PCH_TRANS_LINK_N1 (int) ; 
 int TU_SIZE_MASK ; 
 int TU_SIZE_SHIFT ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void intel_pch_transcoder_get_m_n(struct intel_crtc *crtc,
					 struct intel_link_m_n *m_n)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum pipe pipe = crtc->pipe;

	m_n->link_m = I915_READ(PCH_TRANS_LINK_M1(pipe));
	m_n->link_n = I915_READ(PCH_TRANS_LINK_N1(pipe));
	m_n->gmch_m = I915_READ(PCH_TRANS_DATA_M1(pipe))
		& ~TU_SIZE_MASK;
	m_n->gmch_n = I915_READ(PCH_TRANS_DATA_N1(pipe));
	m_n->tu = ((I915_READ(PCH_TRANS_DATA_M1(pipe))
		    & TU_SIZE_MASK) >> TU_SIZE_SHIFT) + 1;
}