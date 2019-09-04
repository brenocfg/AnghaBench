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
struct drm_i915_private {int /*<<< orphan*/  guc; } ;

/* Variables and functions */
 int GEN9_GUC_TO_HOST_INT_EVENT ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen9_guc_irq_handler(struct drm_i915_private *dev_priv, u32 gt_iir)
{
	if (gt_iir & GEN9_GUC_TO_HOST_INT_EVENT)
		intel_guc_to_host_event_handler(&dev_priv->guc);
}