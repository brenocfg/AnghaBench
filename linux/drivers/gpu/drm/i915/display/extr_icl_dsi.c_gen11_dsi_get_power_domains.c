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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enc_to_intel_dsi (TYPE_1__*) ; 
 int /*<<< orphan*/  get_dsi_io_power_domains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen11_dsi_get_power_domains(struct intel_encoder *encoder,
					struct intel_crtc_state *crtc_state)
{
	get_dsi_io_power_domains(to_i915(encoder->base.dev),
				 enc_to_intel_dsi(&encoder->base));
}