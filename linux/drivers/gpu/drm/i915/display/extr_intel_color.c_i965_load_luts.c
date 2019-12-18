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
struct TYPE_2__ {struct drm_property_blob* gamma_lut; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ gamma_mode; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct drm_property_blob {int dummy; } ;

/* Variables and functions */
 scalar_t__ GAMMA_MODE_MODE_8BIT ; 
 int /*<<< orphan*/  i965_load_lut_10p6 (struct intel_crtc*,struct drm_property_blob const*) ; 
 int /*<<< orphan*/  i9xx_load_luts (struct intel_crtc_state const*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i965_load_luts(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	const struct drm_property_blob *gamma_lut = crtc_state->base.gamma_lut;

	if (crtc_state->gamma_mode == GAMMA_MODE_MODE_8BIT)
		i9xx_load_luts(crtc_state);
	else
		i965_load_lut_10p6(crtc, gamma_lut);
}