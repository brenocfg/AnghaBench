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
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int DBUF_POWER_REQUEST ; 
 int DBUF_POWER_STATE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline
bool intel_dbuf_slice_set(struct drm_i915_private *dev_priv,
			  i915_reg_t reg, bool enable)
{
	u32 val, status;

	val = I915_READ(reg);
	val = enable ? (val | DBUF_POWER_REQUEST) : (val & ~DBUF_POWER_REQUEST);
	I915_WRITE(reg, val);
	POSTING_READ(reg);
	udelay(10);

	status = I915_READ(reg) & DBUF_POWER_STATE;
	if ((enable && !status) || (!enable && status)) {
		DRM_ERROR("DBus power %s timeout!\n",
			  enable ? "enable" : "disable");
		return false;
	}
	return true;
}