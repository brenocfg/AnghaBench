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
struct drm_i915_private {int dummy; } ;
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;

/* Variables and functions */
 int EINVAL ; 
#define  INTEL_PIPE_CRC_SOURCE_NONE 136 
#define  INTEL_PIPE_CRC_SOURCE_PIPE 135 
#define  INTEL_PIPE_CRC_SOURCE_PLANE1 134 
#define  INTEL_PIPE_CRC_SOURCE_PLANE2 133 
#define  INTEL_PIPE_CRC_SOURCE_PLANE3 132 
#define  INTEL_PIPE_CRC_SOURCE_PLANE4 131 
#define  INTEL_PIPE_CRC_SOURCE_PLANE5 130 
#define  INTEL_PIPE_CRC_SOURCE_PLANE6 129 
#define  INTEL_PIPE_CRC_SOURCE_PLANE7 128 

__attribute__((used)) static int skl_crc_source_valid(struct drm_i915_private *dev_priv,
				const enum intel_pipe_crc_source source)
{
	switch (source) {
	case INTEL_PIPE_CRC_SOURCE_PIPE:
	case INTEL_PIPE_CRC_SOURCE_PLANE1:
	case INTEL_PIPE_CRC_SOURCE_PLANE2:
	case INTEL_PIPE_CRC_SOURCE_PLANE3:
	case INTEL_PIPE_CRC_SOURCE_PLANE4:
	case INTEL_PIPE_CRC_SOURCE_PLANE5:
	case INTEL_PIPE_CRC_SOURCE_PLANE6:
	case INTEL_PIPE_CRC_SOURCE_PLANE7:
	case INTEL_PIPE_CRC_SOURCE_NONE:
		return 0;
	default:
		return -EINVAL;
	}
}