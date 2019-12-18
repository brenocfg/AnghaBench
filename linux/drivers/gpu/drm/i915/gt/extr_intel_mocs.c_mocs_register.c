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
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum intel_engine_id { ____Placeholder_intel_engine_id } intel_engine_id ;

/* Variables and functions */
#define  BCS0 133 
 int /*<<< orphan*/  GEN11_MFX2_MOCS (int) ; 
 int /*<<< orphan*/  GEN9_BLT_MOCS (int) ; 
 int /*<<< orphan*/  GEN9_GFX_MOCS (int) ; 
 int /*<<< orphan*/  GEN9_MFX0_MOCS (int) ; 
 int /*<<< orphan*/  GEN9_MFX1_MOCS (int) ; 
 int /*<<< orphan*/  GEN9_VEBOX_MOCS (int) ; 
 int /*<<< orphan*/  INVALID_MMIO_REG ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  RCS0 132 
#define  VCS0 131 
#define  VCS1 130 
#define  VCS2 129 
#define  VECS0 128 

__attribute__((used)) static i915_reg_t mocs_register(enum intel_engine_id engine_id, int index)
{
	switch (engine_id) {
	case RCS0:
		return GEN9_GFX_MOCS(index);
	case VCS0:
		return GEN9_MFX0_MOCS(index);
	case BCS0:
		return GEN9_BLT_MOCS(index);
	case VECS0:
		return GEN9_VEBOX_MOCS(index);
	case VCS1:
		return GEN9_MFX1_MOCS(index);
	case VCS2:
		return GEN11_MFX2_MOCS(index);
	default:
		MISSING_CASE(engine_id);
		return INVALID_MMIO_REG;
	}
}