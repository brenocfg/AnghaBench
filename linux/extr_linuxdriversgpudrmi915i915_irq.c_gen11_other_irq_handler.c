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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ const OTHER_GTPM_INSTANCE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__ const,int /*<<< orphan*/  const) ; 
 void gen6_rps_irq_handler (struct drm_i915_private* const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
gen11_other_irq_handler(struct drm_i915_private * const i915,
			const u8 instance, const u16 iir)
{
	if (instance == OTHER_GTPM_INSTANCE)
		return gen6_rps_irq_handler(i915, iir);

	WARN_ONCE(1, "unhandled other interrupt instance=0x%x, iir=0x%x\n",
		  instance, iir);
}