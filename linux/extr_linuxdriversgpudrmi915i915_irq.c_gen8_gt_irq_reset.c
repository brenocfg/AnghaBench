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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_IRQ_RESET_NDX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GT ; 

__attribute__((used)) static void gen8_gt_irq_reset(struct drm_i915_private *dev_priv)
{
	GEN8_IRQ_RESET_NDX(GT, 0);
	GEN8_IRQ_RESET_NDX(GT, 1);
	GEN8_IRQ_RESET_NDX(GT, 2);
	GEN8_IRQ_RESET_NDX(GT, 3);
}