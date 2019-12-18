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
struct TYPE_2__ {scalar_t__ gamma_lut; int /*<<< orphan*/  ctm; int /*<<< orphan*/  degamma_lut; } ;
struct intel_crtc_state {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ lut_is_legacy (scalar_t__) ; 

__attribute__((used)) static bool crtc_state_is_legacy_gamma(const struct intel_crtc_state *crtc_state)
{
	return !crtc_state->base.degamma_lut &&
		!crtc_state->base.ctm &&
		crtc_state->base.gamma_lut &&
		lut_is_legacy(crtc_state->base.gamma_lut);
}