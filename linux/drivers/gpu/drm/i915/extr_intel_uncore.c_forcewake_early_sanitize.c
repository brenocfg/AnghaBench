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
struct TYPE_2__ {int /*<<< orphan*/  (* force_wake_get ) (struct intel_uncore*,unsigned int) ;} ;
struct intel_uncore {int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo_count; TYPE_1__ funcs; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GTFIFOCTL ; 
 int GT_FIFO_CTL_BLOCK_ALL_POLICY_STALL ; 
 int GT_FIFO_CTL_RC6_POLICY_STALL ; 
 scalar_t__ IS_CHERRYVIEW (int /*<<< orphan*/ ) ; 
 int __raw_uncore_read32 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_uncore_write32 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fifo_free_entries (struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_reset (struct intel_uncore*) ; 
 scalar_t__ intel_uncore_has_fifo (struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_uncore_has_forcewake (struct intel_uncore*) ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int /*<<< orphan*/  iosf_mbi_punit_release () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_uncore*,unsigned int) ; 

__attribute__((used)) static void forcewake_early_sanitize(struct intel_uncore *uncore,
				     unsigned int restore_forcewake)
{
	GEM_BUG_ON(!intel_uncore_has_forcewake(uncore));

	/* WaDisableShadowRegForCpd:chv */
	if (IS_CHERRYVIEW(uncore->i915)) {
		__raw_uncore_write32(uncore, GTFIFOCTL,
				     __raw_uncore_read32(uncore, GTFIFOCTL) |
				     GT_FIFO_CTL_BLOCK_ALL_POLICY_STALL |
				     GT_FIFO_CTL_RC6_POLICY_STALL);
	}

	iosf_mbi_punit_acquire();
	intel_uncore_forcewake_reset(uncore);
	if (restore_forcewake) {
		spin_lock_irq(&uncore->lock);
		uncore->funcs.force_wake_get(uncore, restore_forcewake);

		if (intel_uncore_has_fifo(uncore))
			uncore->fifo_count = fifo_free_entries(uncore);
		spin_unlock_irq(&uncore->lock);
	}
	iosf_mbi_punit_release();
}