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
typedef  scalar_t__ u16 ;
struct intel_guc {int /*<<< orphan*/  doorbell_bitmap; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEN8_DRBREGL (scalar_t__) ; 
 int GEN8_DRB_VALID ; 
 scalar_t__ GUC_DOORBELL_INVALID ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static bool doorbell_ok(struct intel_guc *guc, u16 db_id)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	u32 drbregl;
	bool valid;

	GEM_BUG_ON(db_id >= GUC_DOORBELL_INVALID);

	drbregl = I915_READ(GEN8_DRBREGL(db_id));
	valid = drbregl & GEN8_DRB_VALID;

	if (test_bit(db_id, guc->doorbell_bitmap) == valid)
		return true;

	DRM_DEBUG_DRIVER("Doorbell %d has unexpected state (0x%x): valid=%s\n",
			 db_id, drbregl, yesno(valid));

	return false;
}