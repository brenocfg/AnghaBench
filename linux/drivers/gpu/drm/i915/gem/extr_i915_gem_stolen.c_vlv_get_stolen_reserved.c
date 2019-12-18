#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int end; } ;
struct drm_i915_private {TYPE_1__ dsm; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  GEN6_STOLEN_RESERVED ; 
 int GEN6_STOLEN_RESERVED_ENABLE ; 
#define  GEN7_STOLEN_RESERVED_1M 128 
 int GEN7_STOLEN_RESERVED_SIZE_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static void vlv_get_stolen_reserved(struct drm_i915_private *dev_priv,
				    resource_size_t *base,
				    resource_size_t *size)
{
	u32 reg_val = I915_READ(GEN6_STOLEN_RESERVED);
	resource_size_t stolen_top = dev_priv->dsm.end + 1;

	DRM_DEBUG_DRIVER("GEN6_STOLEN_RESERVED = %08x\n", reg_val);

	if (!(reg_val & GEN6_STOLEN_RESERVED_ENABLE))
		return;

	switch (reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK) {
	default:
		MISSING_CASE(reg_val & GEN7_STOLEN_RESERVED_SIZE_MASK);
		/* fall through */
	case GEN7_STOLEN_RESERVED_1M:
		*size = 1024 * 1024;
		break;
	}

	/*
	 * On vlv, the ADDR_MASK portion is left as 0 and HW deduces the
	 * reserved location as (top - size).
	 */
	*base = stolen_top - *size;
}