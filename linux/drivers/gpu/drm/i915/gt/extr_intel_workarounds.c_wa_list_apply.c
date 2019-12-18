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
struct intel_uncore {int /*<<< orphan*/  lock; } ;
struct i915_wa_list {unsigned int count; int /*<<< orphan*/  name; struct i915_wa* list; } ;
struct i915_wa {int /*<<< orphan*/  reg; int /*<<< orphan*/  val; int /*<<< orphan*/  mask; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG_GEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct intel_uncore*,int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct intel_uncore*,int) ; 
 int /*<<< orphan*/  intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_rmw_fw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wa_verify (struct i915_wa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int wal_get_fw_for_rmw (struct intel_uncore*,struct i915_wa_list const*) ; 

__attribute__((used)) static void
wa_list_apply(struct intel_uncore *uncore, const struct i915_wa_list *wal)
{
	enum forcewake_domains fw;
	unsigned long flags;
	struct i915_wa *wa;
	unsigned int i;

	if (!wal->count)
		return;

	fw = wal_get_fw_for_rmw(uncore, wal);

	spin_lock_irqsave(&uncore->lock, flags);
	intel_uncore_forcewake_get__locked(uncore, fw);

	for (i = 0, wa = wal->list; i < wal->count; i++, wa++) {
		intel_uncore_rmw_fw(uncore, wa->reg, wa->mask, wa->val);
		if (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
			wa_verify(wa,
				  intel_uncore_read_fw(uncore, wa->reg),
				  wal->name, "application");
	}

	intel_uncore_forcewake_put__locked(uncore, fw);
	spin_unlock_irqrestore(&uncore->lock, flags);
}