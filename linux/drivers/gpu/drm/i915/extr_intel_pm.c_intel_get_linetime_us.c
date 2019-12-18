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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ crtc_htotal; } ;
struct TYPE_4__ {TYPE_1__ adjusted_mode; int /*<<< orphan*/  active; } ;
struct intel_crtc_state {scalar_t__ pixel_rate; TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  div_fixed16 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  u32_to_fixed16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint_fixed_16_16_t
intel_get_linetime_us(const struct intel_crtc_state *crtc_state)
{
	u32 pixel_rate;
	u32 crtc_htotal;
	uint_fixed_16_16_t linetime_us;

	if (!crtc_state->base.active)
		return u32_to_fixed16(0);

	pixel_rate = crtc_state->pixel_rate;

	if (WARN_ON(pixel_rate == 0))
		return u32_to_fixed16(0);

	crtc_htotal = crtc_state->base.adjusted_mode.crtc_htotal;
	linetime_us = div_fixed16(crtc_htotal * 1000, pixel_rate);

	return linetime_us;
}