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
struct intel_link_m_n {int gmch_m; int gmch_n; int link_m; int link_n; int /*<<< orphan*/  tu; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__* config; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
struct TYPE_4__ {int cpu_transcoder; scalar_t__ has_drrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_DATA_M1 (int) ; 
 int /*<<< orphan*/  PIPE_DATA_M2 (int) ; 
 int /*<<< orphan*/  PIPE_DATA_M_G4X (int) ; 
 int /*<<< orphan*/  PIPE_DATA_N1 (int) ; 
 int /*<<< orphan*/  PIPE_DATA_N2 (int) ; 
 int /*<<< orphan*/  PIPE_DATA_N_G4X (int) ; 
 int /*<<< orphan*/  PIPE_LINK_M1 (int) ; 
 int /*<<< orphan*/  PIPE_LINK_M2 (int) ; 
 int /*<<< orphan*/  PIPE_LINK_M_G4X (int) ; 
 int /*<<< orphan*/  PIPE_LINK_N1 (int) ; 
 int /*<<< orphan*/  PIPE_LINK_N2 (int) ; 
 int /*<<< orphan*/  PIPE_LINK_N_G4X (int) ; 
 int TU_SIZE (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_cpu_transcoder_set_m_n(struct intel_crtc *crtc,
					 struct intel_link_m_n *m_n,
					 struct intel_link_m_n *m2_n2)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	int pipe = crtc->pipe;
	enum transcoder transcoder = crtc->config->cpu_transcoder;

	if (INTEL_GEN(dev_priv) >= 5) {
		I915_WRITE(PIPE_DATA_M1(transcoder), TU_SIZE(m_n->tu) | m_n->gmch_m);
		I915_WRITE(PIPE_DATA_N1(transcoder), m_n->gmch_n);
		I915_WRITE(PIPE_LINK_M1(transcoder), m_n->link_m);
		I915_WRITE(PIPE_LINK_N1(transcoder), m_n->link_n);
		/* M2_N2 registers to be set only for gen < 8 (M2_N2 available
		 * for gen < 8) and if DRRS is supported (to make sure the
		 * registers are not unnecessarily accessed).
		 */
		if (m2_n2 && (IS_CHERRYVIEW(dev_priv) ||
		    INTEL_GEN(dev_priv) < 8) && crtc->config->has_drrs) {
			I915_WRITE(PIPE_DATA_M2(transcoder),
					TU_SIZE(m2_n2->tu) | m2_n2->gmch_m);
			I915_WRITE(PIPE_DATA_N2(transcoder), m2_n2->gmch_n);
			I915_WRITE(PIPE_LINK_M2(transcoder), m2_n2->link_m);
			I915_WRITE(PIPE_LINK_N2(transcoder), m2_n2->link_n);
		}
	} else {
		I915_WRITE(PIPE_DATA_M_G4X(pipe), TU_SIZE(m_n->tu) | m_n->gmch_m);
		I915_WRITE(PIPE_DATA_N_G4X(pipe), m_n->gmch_n);
		I915_WRITE(PIPE_LINK_M_G4X(pipe), m_n->link_m);
		I915_WRITE(PIPE_LINK_N_G4X(pipe), m_n->link_n);
	}
}