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
struct intel_crtc_state {int /*<<< orphan*/  shared_dpll; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int DPLL_ID_SKL_DPLL0 ; 
 int DPLL_ID_SKL_DPLL1 ; 
 int DPLL_ID_SKL_DPLL2 ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  PORT_A 130 
#define  PORT_B 129 
#define  PORT_C 128 
 int /*<<< orphan*/  intel_get_shared_dpll_by_id (struct drm_i915_private*,int) ; 

__attribute__((used)) static void bxt_get_ddi_pll(struct drm_i915_private *dev_priv,
				enum port port,
				struct intel_crtc_state *pipe_config)
{
	enum intel_dpll_id id;

	switch (port) {
	case PORT_A:
		id = DPLL_ID_SKL_DPLL0;
		break;
	case PORT_B:
		id = DPLL_ID_SKL_DPLL1;
		break;
	case PORT_C:
		id = DPLL_ID_SKL_DPLL2;
		break;
	default:
		DRM_ERROR("Incorrect port type\n");
		return;
	}

	pipe_config->shared_dpll = intel_get_shared_dpll_by_id(dev_priv, id);
}