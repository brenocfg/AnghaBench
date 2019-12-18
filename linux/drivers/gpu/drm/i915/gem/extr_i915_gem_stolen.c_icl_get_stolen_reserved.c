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
typedef  int u64 ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int GEN11_STOLEN_RESERVED_ADDR_MASK ; 
 int /*<<< orphan*/  GEN6_STOLEN_RESERVED ; 
#define  GEN8_STOLEN_RESERVED_1M 131 
#define  GEN8_STOLEN_RESERVED_2M 130 
#define  GEN8_STOLEN_RESERVED_4M 129 
#define  GEN8_STOLEN_RESERVED_8M 128 
 int GEN8_STOLEN_RESERVED_SIZE_MASK ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int intel_uncore_read64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_get_stolen_reserved(struct drm_i915_private *i915,
				    resource_size_t *base,
				    resource_size_t *size)
{
	u64 reg_val = intel_uncore_read64(&i915->uncore, GEN6_STOLEN_RESERVED);

	DRM_DEBUG_DRIVER("GEN6_STOLEN_RESERVED = 0x%016llx\n", reg_val);

	*base = reg_val & GEN11_STOLEN_RESERVED_ADDR_MASK;

	switch (reg_val & GEN8_STOLEN_RESERVED_SIZE_MASK) {
	case GEN8_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		break;
	case GEN8_STOLEN_RESERVED_2M:
		*size = 2 * 1024 * 1024;
		break;
	case GEN8_STOLEN_RESERVED_4M:
		*size = 4 * 1024 * 1024;
		break;
	case GEN8_STOLEN_RESERVED_8M:
		*size = 8 * 1024 * 1024;
		break;
	default:
		*size = 8 * 1024 * 1024;
		MISSING_CASE(reg_val & GEN8_STOLEN_RESERVED_SIZE_MASK);
	}
}