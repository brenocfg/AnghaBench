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
#define  INTEL_PIPE_CRC_SOURCE_NONE 131 
#define  INTEL_PIPE_CRC_SOURCE_PIPE 130 
#define  INTEL_PIPE_CRC_SOURCE_PLANE1 129 
#define  INTEL_PIPE_CRC_SOURCE_PLANE2 128 
 int PIPE_CRC_ENABLE ; 
 int PIPE_CRC_SOURCE_PF_IVB ; 
 int PIPE_CRC_SOURCE_PRIMARY_IVB ; 
 int PIPE_CRC_SOURCE_SPRITE_IVB ; 

__attribute__((used)) static int ivb_pipe_crc_ctl_reg(struct drm_i915_private *dev_priv,
				enum pipe pipe,
				enum intel_pipe_crc_source *source,
				u32 *val)
{
	if (*source == INTEL_PIPE_CRC_SOURCE_AUTO)
		*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	switch (*source) {
	case INTEL_PIPE_CRC_SOURCE_PLANE1:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PRIMARY_IVB;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE2:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_SPRITE_IVB;
		break;
	case INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PF_IVB;
		break;
	case INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}