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
struct TYPE_2__ {scalar_t__ gamma_lut; scalar_t__ degamma_lut; } ;
struct intel_crtc_state {TYPE_1__ base; int /*<<< orphan*/  c8_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED ; 
 int /*<<< orphan*/  GAMMA_MODE_MODE_8BIT ; 
 int /*<<< orphan*/  POST_CSC_GAMMA_ENABLE ; 
 int /*<<< orphan*/  PRE_CSC_GAMMA_ENABLE ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct intel_crtc_state const*) ; 

__attribute__((used)) static u32 icl_gamma_mode(const struct intel_crtc_state *crtc_state)
{
	u32 gamma_mode = 0;

	if (crtc_state->base.degamma_lut)
		gamma_mode |= PRE_CSC_GAMMA_ENABLE;

	if (crtc_state->base.gamma_lut &&
	    !crtc_state->c8_planes)
		gamma_mode |= POST_CSC_GAMMA_ENABLE;

	if (!crtc_state->base.gamma_lut ||
	    crtc_state_is_legacy_gamma(crtc_state))
		gamma_mode |= GAMMA_MODE_MODE_8BIT;
	else
		gamma_mode |= GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED;

	return gamma_mode;
}