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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_dp {int lane_count; int link_rate; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_PORT_CL1CM_DW5 ; 
 int /*<<< orphan*/  CNL_PORT_PCS_DW1_GRP (int) ; 
 int /*<<< orphan*/  CNL_PORT_PCS_DW1_LN0 (int) ; 
 int /*<<< orphan*/  CNL_PORT_TX_DW4_LN (int,int) ; 
 int /*<<< orphan*/  CNL_PORT_TX_DW5_GRP (int) ; 
 int /*<<< orphan*/  CNL_PORT_TX_DW5_LN0 (int) ; 
 int /*<<< orphan*/  COMMON_KEEPER_EN ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  LOADGEN_SELECT ; 
 int /*<<< orphan*/  SUS_CLOCK_CONFIG ; 
 int /*<<< orphan*/  TX_TRAINING_EN ; 
 int /*<<< orphan*/  cnl_ddi_vswing_program (struct intel_encoder*,int,int) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_1__*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_ddi_vswing_sequence(struct intel_encoder *encoder,
				    int level, enum intel_output_type type)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	int width, rate, ln;
	u32 val;

	if (type == INTEL_OUTPUT_HDMI) {
		width = 4;
		rate = 0; /* Rate is always < than 6GHz for HDMI */
	} else {
		struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);

		width = intel_dp->lane_count;
		rate = intel_dp->link_rate;
	}

	/*
	 * 1. If port type is eDP or DP,
	 * set PORT_PCS_DW1 cmnkeeper_enable to 1b,
	 * else clear to 0b.
	 */
	val = I915_READ(CNL_PORT_PCS_DW1_LN0(port));
	if (type != INTEL_OUTPUT_HDMI)
		val |= COMMON_KEEPER_EN;
	else
		val &= ~COMMON_KEEPER_EN;
	I915_WRITE(CNL_PORT_PCS_DW1_GRP(port), val);

	/* 2. Program loadgen select */
	/*
	 * Program PORT_TX_DW4_LN depending on Bit rate and used lanes
	 * <= 6 GHz and 4 lanes (LN0=0, LN1=1, LN2=1, LN3=1)
	 * <= 6 GHz and 1,2 lanes (LN0=0, LN1=1, LN2=1, LN3=0)
	 * > 6 GHz (LN0=0, LN1=0, LN2=0, LN3=0)
	 */
	for (ln = 0; ln <= 3; ln++) {
		val = I915_READ(CNL_PORT_TX_DW4_LN(ln, port));
		val &= ~LOADGEN_SELECT;

		if ((rate <= 600000 && width == 4 && ln >= 1)  ||
		    (rate <= 600000 && width < 4 && (ln == 1 || ln == 2))) {
			val |= LOADGEN_SELECT;
		}
		I915_WRITE(CNL_PORT_TX_DW4_LN(ln, port), val);
	}

	/* 3. Set PORT_CL_DW5 SUS Clock Config to 11b */
	val = I915_READ(CNL_PORT_CL1CM_DW5);
	val |= SUS_CLOCK_CONFIG;
	I915_WRITE(CNL_PORT_CL1CM_DW5, val);

	/* 4. Clear training enable to change swing values */
	val = I915_READ(CNL_PORT_TX_DW5_LN0(port));
	val &= ~TX_TRAINING_EN;
	I915_WRITE(CNL_PORT_TX_DW5_GRP(port), val);

	/* 5. Program swing and de-emphasis */
	cnl_ddi_vswing_program(encoder, level, type);

	/* 6. Set training enable to trigger update */
	val = I915_READ(CNL_PORT_TX_DW5_LN0(port));
	val |= TX_TRAINING_EN;
	I915_WRITE(CNL_PORT_TX_DW5_GRP(port), val);
}