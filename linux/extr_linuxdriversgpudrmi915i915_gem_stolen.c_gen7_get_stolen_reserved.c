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
typedef  int resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  GEN6_STOLEN_RESERVED ; 
 int GEN6_STOLEN_RESERVED_ENABLE ; 
#define  GEN7_STOLEN_RESERVED_1M 129 
#define  GEN7_STOLEN_RESERVED_256K 128 
 int GEN7_STOLEN_RESERVED_ADDR_MASK ; 
 int GEN7_STOLEN_RESERVED_SIZE_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static void gen7_get_stolen_reserved(struct drm_i915_private *dev_priv,
				     resource_size_t *base,
				     resource_size_t *size)
{
	u32 reg_val = I915_READ(GEN6_STOLEN_RESERVED);

	DRM_DEBUG_DRIVER("GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	if (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		return;

	*base = reg_val & GEN7_STOLEN_RESERVED_ADDR_MASK;

	switch (reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK) {
	case GEN7_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		break;
	case GEN7_STOLEN_RESERVED_256K:
		*size = 256 * 1024;
		break;
	default:
		*size = 1024 * 1024;
		MISSING_CASE(reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK);
	}
}