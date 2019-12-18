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
typedef  int u16 ;
struct intel_uncore {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fstart; } ;
struct drm_i915_private {TYPE_1__ ips; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEIER ; 
 int /*<<< orphan*/  DEIIR ; 
 int /*<<< orphan*/  DEIMR ; 
 int DE_PCU_EVENT ; 
 int MEMCTL_CMD_STS ; 
 int /*<<< orphan*/  MEMINTREN ; 
 int /*<<< orphan*/  MEMINTRSTS ; 
 int MEMINT_EVAL_CHG ; 
 int MEMINT_EVAL_CHG_EN ; 
 int /*<<< orphan*/  MEMSWCTL ; 
 int intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int intel_uncore_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ironlake_set_drps (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_disable_drps(struct drm_i915_private *i915)
{
	struct intel_uncore *uncore = &i915->uncore;
	u16 rgvswctl;

	spin_lock_irq(&mchdev_lock);

	rgvswctl = intel_uncore_read16(uncore, MEMSWCTL);

	/* Ack interrupts, disable EFC interrupt */
	intel_uncore_write(uncore,
			   MEMINTREN,
			   intel_uncore_read(uncore, MEMINTREN) &
			   ~MEMINT_EVAL_CHG_EN);
	intel_uncore_write(uncore, MEMINTRSTS, MEMINT_EVAL_CHG);
	intel_uncore_write(uncore,
			   DEIER,
			   intel_uncore_read(uncore, DEIER) & ~DE_PCU_EVENT);
	intel_uncore_write(uncore, DEIIR, DE_PCU_EVENT);
	intel_uncore_write(uncore,
			   DEIMR,
			   intel_uncore_read(uncore, DEIMR) | DE_PCU_EVENT);

	/* Go back to the starting frequency */
	ironlake_set_drps(i915, i915->ips.fstart);
	mdelay(1);
	rgvswctl |= MEMCTL_CMD_STS;
	intel_uncore_write(uncore, MEMSWCTL, rgvswctl);
	mdelay(1);

	spin_unlock_irq(&mchdev_lock);
}