#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct intel_uncore_forcewake_domain {int wake_count; int id; TYPE_2__ timer; int /*<<< orphan*/  mask; void* reg_ack; void* reg_set; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_domains; struct intel_uncore_forcewake_domain* fw_domain; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  void* i915_reg_t ;
typedef  enum forcewake_domain_id { ____Placeholder_forcewake_domain_id } forcewake_domain_id ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int FORCEWAKE_BLITTER ; 
 int FORCEWAKE_MEDIA ; 
 int FORCEWAKE_MEDIA_VDBOX0 ; 
 int FORCEWAKE_MEDIA_VDBOX1 ; 
 int FORCEWAKE_MEDIA_VDBOX2 ; 
 int FORCEWAKE_MEDIA_VDBOX3 ; 
 int FORCEWAKE_MEDIA_VEBOX0 ; 
 int FORCEWAKE_MEDIA_VEBOX1 ; 
 int FORCEWAKE_RENDER ; 
 int FW_DOMAIN_ID_BLITTER ; 
 int FW_DOMAIN_ID_COUNT ; 
 int FW_DOMAIN_ID_MEDIA ; 
 int FW_DOMAIN_ID_MEDIA_VDBOX0 ; 
 int FW_DOMAIN_ID_MEDIA_VDBOX1 ; 
 int FW_DOMAIN_ID_MEDIA_VDBOX2 ; 
 int FW_DOMAIN_ID_MEDIA_VDBOX3 ; 
 int FW_DOMAIN_ID_MEDIA_VEBOX0 ; 
 int FW_DOMAIN_ID_MEDIA_VEBOX1 ; 
 int FW_DOMAIN_ID_RENDER ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fw_domain_reset (struct drm_i915_private*,struct intel_uncore_forcewake_domain*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_valid (void*) ; 
 int /*<<< orphan*/  intel_uncore_fw_release_timer ; 

__attribute__((used)) static void fw_domain_init(struct drm_i915_private *dev_priv,
			   enum forcewake_domain_id domain_id,
			   i915_reg_t reg_set,
			   i915_reg_t reg_ack)
{
	struct intel_uncore_forcewake_domain *d;

	if (WARN_ON(domain_id >= FW_DOMAIN_ID_COUNT))
		return;

	d = &dev_priv->uncore.fw_domain[domain_id];

	WARN_ON(d->wake_count);

	WARN_ON(!i915_mmio_reg_valid(reg_set));
	WARN_ON(!i915_mmio_reg_valid(reg_ack));

	d->wake_count = 0;
	d->reg_set = reg_set;
	d->reg_ack = reg_ack;

	d->id = domain_id;

	BUILD_BUG_ON(FORCEWAKE_RENDER != (1 << FW_DOMAIN_ID_RENDER));
	BUILD_BUG_ON(FORCEWAKE_BLITTER != (1 << FW_DOMAIN_ID_BLITTER));
	BUILD_BUG_ON(FORCEWAKE_MEDIA != (1 << FW_DOMAIN_ID_MEDIA));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX0 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX0));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX1 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX1));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX2 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX2));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX3 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX3));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VEBOX0 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX0));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VEBOX1 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX1));


	d->mask = BIT(domain_id);

	hrtimer_init(&d->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	d->timer.function = intel_uncore_fw_release_timer;

	dev_priv->uncore.fw_domains |= BIT(domain_id);

	fw_domain_reset(dev_priv, d);
}