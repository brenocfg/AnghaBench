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
struct intel_uncore {int dummy; } ;
struct intel_gmbus {int /*<<< orphan*/  gpio_reg; struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {struct intel_uncore uncore; } ;

/* Variables and functions */
 int GPIO_CLOCK_PULLUP_DISABLE ; 
 int GPIO_DATA_PULLUP_DISABLE ; 
 int /*<<< orphan*/  IS_I830 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_I845G (struct drm_i915_private*) ; 
 int intel_uncore_read_notrace (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_reserved(struct intel_gmbus *bus)
{
	struct drm_i915_private *i915 = bus->dev_priv;
	struct intel_uncore *uncore = &i915->uncore;
	u32 reserved = 0;

	/* On most chips, these bits must be preserved in software. */
	if (!IS_I830(i915) && !IS_I845G(i915))
		reserved = intel_uncore_read_notrace(uncore, bus->gpio_reg) &
			   (GPIO_DATA_PULLUP_DISABLE |
			    GPIO_CLOCK_PULLUP_DISABLE);

	return reserved;
}