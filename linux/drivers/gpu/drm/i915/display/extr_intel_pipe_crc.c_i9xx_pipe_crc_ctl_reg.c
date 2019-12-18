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
 int EINVAL ; 
 int INTEL_PIPE_CRC_SOURCE_AUTO ; 
#define  INTEL_PIPE_CRC_SOURCE_NONE 130 
#define  INTEL_PIPE_CRC_SOURCE_PIPE 129 
#define  INTEL_PIPE_CRC_SOURCE_TV 128 
 int PIPE_CRC_ENABLE ; 
 int PIPE_CRC_SOURCE_PIPE_I9XX ; 
 int PIPE_CRC_SOURCE_TV_PRE ; 
 int /*<<< orphan*/  SUPPORTS_TV (struct drm_i915_private*) ; 
 int i9xx_pipe_crc_auto_source (struct drm_i915_private*,int,int*) ; 

__attribute__((used)) static int i9xx_pipe_crc_ctl_reg(struct drm_i915_private *dev_priv,
				 enum pipe pipe,
				 enum intel_pipe_crc_source *source,
				 u32 *val)
{
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
	case INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		break;
	default:
		/*
		 * The DP CRC source doesn't work on g4x.
		 * It can be made to work to some degree by selecting
		 * the correct CRC source before the port is enabled,
		 * and not touching the CRC source bits again until
		 * the port is disabled. But even then the bits
		 * eventually get stuck and a reboot is needed to get
		 * working CRCs on the pipe again. Let's simply
		 * refuse to use DP CRCs on g4x.
		 */
		return -EINVAL;
	}

	return 0;
}