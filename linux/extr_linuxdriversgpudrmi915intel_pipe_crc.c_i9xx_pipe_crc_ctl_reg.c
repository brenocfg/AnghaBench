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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;

/* Variables and functions */
 int DC_BALANCE_RESET ; 
 int EINVAL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_PIPE_CRC_SOURCE_AUTO ; 
#define  INTEL_PIPE_CRC_SOURCE_DP_B 133 
#define  INTEL_PIPE_CRC_SOURCE_DP_C 132 
#define  INTEL_PIPE_CRC_SOURCE_DP_D 131 
#define  INTEL_PIPE_CRC_SOURCE_NONE 130 
#define  INTEL_PIPE_CRC_SOURCE_PIPE 129 
#define  INTEL_PIPE_CRC_SOURCE_TV 128 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 int PIPE_A ; 
 int PIPE_A_SCRAMBLE_RESET ; 
 int PIPE_B_SCRAMBLE_RESET ; 
 int PIPE_CRC_ENABLE ; 
 int PIPE_CRC_SOURCE_DP_B_G4X ; 
 int PIPE_CRC_SOURCE_DP_C_G4X ; 
 int PIPE_CRC_SOURCE_DP_D_G4X ; 
 int PIPE_CRC_SOURCE_PIPE_I9XX ; 
 int PIPE_CRC_SOURCE_TV_PRE ; 
 int /*<<< orphan*/  PORT_DFT2_G4X ; 
 int /*<<< orphan*/  PORT_DFT_I9XX ; 
 int /*<<< orphan*/  SUPPORTS_TV (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int i9xx_pipe_crc_auto_source (struct drm_i915_private*,int,int*) ; 

__attribute__((used)) static int i9xx_pipe_crc_ctl_reg(struct drm_i915_private *dev_priv,
				 enum pipe pipe,
				 enum intel_pipe_crc_source *source,
				 uint32_t *val)
{
	bool need_stable_symbols = false;

	if (*source == INTEL_PIPE_CRC_SOURCE_AUTO) {
		int ret = i9xx_pipe_crc_auto_source(dev_priv, pipe, source);
		if (ret)
			return ret;
	}

	switch (*source) {
	case INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PIPE_I9XX;
		break;
	case INTEL_PIPE_CRC_SOURCE_TV:
		if (!SUPPORTS_TV(dev_priv))
			return -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_TV_PRE;
		break;
	case INTEL_PIPE_CRC_SOURCE_DP_B:
		if (!IS_G4X(dev_priv))
			return -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_B_G4X;
		need_stable_symbols = true;
		break;
	case INTEL_PIPE_CRC_SOURCE_DP_C:
		if (!IS_G4X(dev_priv))
			return -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_C_G4X;
		need_stable_symbols = true;
		break;
	case INTEL_PIPE_CRC_SOURCE_DP_D:
		if (!IS_G4X(dev_priv))
			return -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_D_G4X;
		need_stable_symbols = true;
		break;
	case INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		break;
	default:
		return -EINVAL;
	}

	/*
	 * When the pipe CRC tap point is after the transcoders we need
	 * to tweak symbol-level features to produce a deterministic series of
	 * symbols for a given frame. We need to reset those features only once
	 * a frame (instead of every nth symbol):
	 *   - DC-balance: used to ensure a better clock recovery from the data
	 *     link (SDVO)
	 *   - DisplayPort scrambling: used for EMI reduction
	 */
	if (need_stable_symbols) {
		uint32_t tmp = I915_READ(PORT_DFT2_G4X);

		WARN_ON(!IS_G4X(dev_priv));

		I915_WRITE(PORT_DFT_I9XX,
			   I915_READ(PORT_DFT_I9XX) | DC_BALANCE_RESET);

		if (pipe == PIPE_A)
			tmp |= PIPE_A_SCRAMBLE_RESET;
		else
			tmp |= PIPE_B_SCRAMBLE_RESET;

		I915_WRITE(PORT_DFT2_G4X, tmp);
	}

	return 0;
}