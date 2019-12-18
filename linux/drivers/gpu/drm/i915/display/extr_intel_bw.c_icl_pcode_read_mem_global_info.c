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
struct intel_qgv_info {scalar_t__ dram_type; int num_channels; int num_points; int t_bl; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ICL_PCODE_MEM_SS_READ_GLOBAL_INFO ; 
 int ICL_PCODE_MEM_SUBSYSYSTEM_INFO ; 
 scalar_t__ INTEL_DRAM_DDR3 ; 
 scalar_t__ INTEL_DRAM_DDR4 ; 
 void* INTEL_DRAM_LPDDR3 ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int sandybridge_pcode_read (struct drm_i915_private*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int icl_pcode_read_mem_global_info(struct drm_i915_private *dev_priv,
					  struct intel_qgv_info *qi)
{
	u32 val = 0;
	int ret;

	ret = sandybridge_pcode_read(dev_priv,
				     ICL_PCODE_MEM_SUBSYSYSTEM_INFO |
				     ICL_PCODE_MEM_SS_READ_GLOBAL_INFO,
				     &val, NULL);
	if (ret)
		return ret;

	switch (val & 0xf) {
	case 0:
		qi->dram_type = INTEL_DRAM_DDR4;
		break;
	case 1:
		qi->dram_type = INTEL_DRAM_DDR3;
		break;
	case 2:
		qi->dram_type = INTEL_DRAM_LPDDR3;
		break;
	case 3:
		qi->dram_type = INTEL_DRAM_LPDDR3;
		break;
	default:
		MISSING_CASE(val & 0xf);
		break;
	}

	qi->num_channels = (val & 0xf0) >> 4;
	qi->num_points = (val & 0xf00) >> 8;

	qi->t_bl = qi->dram_type == INTEL_DRAM_DDR4 ? 4 : 8;

	return 0;
}