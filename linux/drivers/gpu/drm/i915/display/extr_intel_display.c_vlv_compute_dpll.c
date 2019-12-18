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
struct TYPE_2__ {int dpll; int dpll_md; } ;
struct intel_crtc_state {int pixel_multiplier; TYPE_1__ dpll_hw_state; } ;
struct intel_crtc {scalar_t__ pipe; } ;

/* Variables and functions */
 int DPLL_EXT_BUFFER_ENABLE_VLV ; 
 int DPLL_INTEGRATED_CRI_CLK_VLV ; 
 int DPLL_INTEGRATED_REF_CLK_VLV ; 
 int DPLL_MD_UDI_MULTIPLIER_SHIFT ; 
 int DPLL_REF_CLK_ENABLE_VLV ; 
 int DPLL_VCO_ENABLE ; 
 int DPLL_VGA_MODE_DIS ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 scalar_t__ PIPE_A ; 
 int /*<<< orphan*/  intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlv_compute_dpll(struct intel_crtc *crtc,
			     struct intel_crtc_state *pipe_config)
{
	pipe_config->dpll_hw_state.dpll = DPLL_INTEGRATED_REF_CLK_VLV |
		DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
	if (crtc->pipe != PIPE_A)
		pipe_config->dpll_hw_state.dpll |= DPLL_INTEGRATED_CRI_CLK_VLV;

	/* DPLL not used with DSI, but still need the rest set up */
	if (!intel_crtc_has_type(pipe_config, INTEL_OUTPUT_DSI))
		pipe_config->dpll_hw_state.dpll |= DPLL_VCO_ENABLE |
			DPLL_EXT_BUFFER_ENABLE_VLV;

	pipe_config->dpll_hw_state.dpll_md =
		(pipe_config->pixel_multiplier - 1) << DPLL_MD_UDI_MULTIPLIER_SHIFT;
}