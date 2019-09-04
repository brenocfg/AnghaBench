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
struct drm_crtc_state {int /*<<< orphan*/  gamma_lut; int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  i9xx_load_luts_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void i9xx_load_luts(struct drm_crtc_state *crtc_state)
{
	i9xx_load_luts_internal(crtc_state->crtc, crtc_state->gamma_lut,
				to_intel_crtc_state(crtc_state));
}