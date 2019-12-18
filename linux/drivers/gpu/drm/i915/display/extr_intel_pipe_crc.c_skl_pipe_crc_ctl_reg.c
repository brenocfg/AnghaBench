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
#define  INTEL_PIPE_CRC_SOURCE_NONE 136 
#define  INTEL_PIPE_CRC_SOURCE_PIPE 135 
#define  INTEL_PIPE_CRC_SOURCE_PLANE1 134 
#define  INTEL_PIPE_CRC_SOURCE_PLANE2 133 
#define  INTEL_PIPE_CRC_SOURCE_PLANE3 132 
#define  INTEL_PIPE_CRC_SOURCE_PLANE4 131 
#define  INTEL_PIPE_CRC_SOURCE_PLANE5 130 
#define  INTEL_PIPE_CRC_SOURCE_PLANE6 129 
#define  INTEL_PIPE_CRC_SOURCE_PLANE7 128 
 int PIPE_CRC_ENABLE ; 
 int PIPE_CRC_SOURCE_DMUX_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_1_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_2_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_3_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_4_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_5_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_6_SKL ; 
 int PIPE_CRC_SOURCE_PLANE_7_SKL ; 

__attribute__((used)) static int skl_pipe_crc_ctl_reg(struct drm_i915_private *dev_priv,
				enum pipe pipe,
				enum intel_pipe_crc_source *source,
				u32 *val)
{
	if (*source == INTEL_PIPE_CRC_SOURCE_AUTO)
		*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	switch (*source) {
	case INTEL_PIPE_CRC_SOURCE_PLANE1:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_1_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE2:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_2_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE3:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_3_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE4:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_4_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE5:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_5_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE6:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_6_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PLANE7:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_7_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DMUX_SKL;
		break;
	case INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}