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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;

/* Variables and functions */
 int DC_BALANCE_RESET_VLV ; 
 int EINVAL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_PIPE_CRC_SOURCE_AUTO ; 
#define  INTEL_PIPE_CRC_SOURCE_DP_B 135 
#define  INTEL_PIPE_CRC_SOURCE_DP_C 134 
#define  INTEL_PIPE_CRC_SOURCE_DP_D 133 
#define  INTEL_PIPE_CRC_SOURCE_NONE 132 
#define  INTEL_PIPE_CRC_SOURCE_PIPE 131 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
#define  PIPE_A 130 
 int PIPE_A_SCRAMBLE_RESET ; 
#define  PIPE_B 129 
 int PIPE_B_SCRAMBLE_RESET ; 
#define  PIPE_C 128 
 int PIPE_CRC_ENABLE ; 
 int PIPE_CRC_SOURCE_DP_B_VLV ; 
 int PIPE_CRC_SOURCE_DP_C_VLV ; 
 int PIPE_CRC_SOURCE_DP_D_VLV ; 
 int PIPE_CRC_SOURCE_PIPE_VLV ; 
 int PIPE_C_SCRAMBLE_RESET ; 
 int /*<<< orphan*/  PORT_DFT2_G4X ; 
 int i9xx_pipe_crc_auto_source (struct drm_i915_private*,int,int*) ; 

__attribute__((used)) static int vlv_pipe_crc_ctl_reg(struct drm_i915_private *dev_priv,
				enum pipe pipe,
				enum intel_pipe_crc_source *source,
				u32 *val)
{
	bool need_stable_symbols = false;

	if (*source == INTEL_PIPE_CRC_SOURCE_AUTO) {
		int ret = i9xx_pipe_crc_auto_source(dev_priv, pipe, source);
		if (ret)
			return ret;
	}

	switch (*source) {
	case INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PIPE_VLV;
		break;
	case INTEL_PIPE_CRC_SOURCE_DP_B:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_B_VLV;
		need_stable_symbols = true;
		break;
	case INTEL_PIPE_CRC_SOURCE_DP_C:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_C_VLV;
		need_stable_symbols = true;
		break;
	case INTEL_PIPE_CRC_SOURCE_DP_D:
		if (!IS_CHERRYVIEW(dev_priv))
			return -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_D_VLV;
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
		u32 tmp = I915_READ(PORT_DFT2_G4X);

		tmp |= DC_BALANCE_RESET_VLV;
		switch (pipe) {
		case PIPE_A:
			tmp |= PIPE_A_SCRAMBLE_RESET;
			break;
		case PIPE_B:
			tmp |= PIPE_B_SCRAMBLE_RESET;
			break;
		case PIPE_C:
			tmp |= PIPE_C_SCRAMBLE_RESET;
			break;
		default:
			return -EINVAL;
		}
		I915_WRITE(PORT_DFT2_G4X, tmp);
	}

	return 0;
}