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
struct TYPE_2__ {int /*<<< orphan*/  gamma_lut; } ;
struct intel_crtc_state {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  i9xx_load_luts_internal (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_load_luts(const struct intel_crtc_state *crtc_state)
{
	i9xx_load_luts_internal(crtc_state, crtc_state->base.gamma_lut);
}