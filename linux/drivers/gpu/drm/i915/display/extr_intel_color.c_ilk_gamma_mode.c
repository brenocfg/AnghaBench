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
typedef  int /*<<< orphan*/  u32 ;
struct intel_crtc_state {int /*<<< orphan*/  gamma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE_MODE_10BIT ; 
 int /*<<< orphan*/  GAMMA_MODE_MODE_8BIT ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct intel_crtc_state const*) ; 

__attribute__((used)) static u32 ilk_gamma_mode(const struct intel_crtc_state *crtc_state)
{
	if (!crtc_state->gamma_enable ||
	    crtc_state_is_legacy_gamma(crtc_state))
		return GAMMA_MODE_MODE_8BIT;
	else
		return GAMMA_MODE_MODE_10BIT;
}