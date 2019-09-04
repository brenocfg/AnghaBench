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
struct intel_encoder {int type; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  output_reg; } ;

/* Variables and functions */
#define  INTEL_OUTPUT_DDI 130 
#define  INTEL_OUTPUT_DP 129 
#define  INTEL_OUTPUT_EDP 128 
 TYPE_1__* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int i915_mmio_reg_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool intel_encoder_is_dp(struct intel_encoder *encoder)
{
	switch (encoder->type) {
	case INTEL_OUTPUT_DP:
	case INTEL_OUTPUT_EDP:
		return true;
	case INTEL_OUTPUT_DDI:
		/* Skip pure HDMI/DVI DDI encoders */
		return i915_mmio_reg_valid(enc_to_intel_dp(&encoder->base)->output_reg);
	default:
		return false;
	}
}