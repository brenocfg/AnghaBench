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
typedef  int u8 ;
typedef  int u16 ;
struct intel_uncore {int dummy; } ;
struct drm_i915_private {struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int MEMCTL_CMD_CHFREQ ; 
 int MEMCTL_CMD_SHIFT ; 
 int MEMCTL_CMD_STS ; 
 int MEMCTL_FREQ_SHIFT ; 
 int MEMCTL_SFCAVM ; 
 int /*<<< orphan*/  MEMSWCTL ; 
 int /*<<< orphan*/  intel_uncore_posting_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int intel_uncore_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write16 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mchdev_lock ; 

bool ironlake_set_drps(struct drm_i915_private *i915, u8 val)
{
	struct intel_uncore *uncore = &i915->uncore;
	u16 rgvswctl;

	lockdep_assert_held(&mchdev_lock);

	rgvswctl = intel_uncore_read16(uncore, MEMSWCTL);
	if (rgvswctl & MEMCTL_CMD_STS) {
		DRM_DEBUG("gpu busy, RCS change rejected\n");
		return false; /* still busy with another command */
	}

	rgvswctl = (MEMCTL_CMD_CHFREQ << MEMCTL_CMD_SHIFT) |
		(val << MEMCTL_FREQ_SHIFT) | MEMCTL_SFCAVM;
	intel_uncore_write16(uncore, MEMSWCTL, rgvswctl);
	intel_uncore_posting_read16(uncore, MEMSWCTL);

	rgvswctl |= MEMCTL_CMD_STS;
	intel_uncore_write16(uncore, MEMSWCTL, rgvswctl);

	return true;
}