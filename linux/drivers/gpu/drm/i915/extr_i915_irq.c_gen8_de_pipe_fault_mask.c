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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_DE_PIPE_IRQ_FAULT_ERRORS ; 
 int /*<<< orphan*/  GEN9_DE_PIPE_IRQ_FAULT_ERRORS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static u32 gen8_de_pipe_fault_mask(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 9)
		return GEN9_DE_PIPE_IRQ_FAULT_ERRORS;
	else
		return GEN8_DE_PIPE_IRQ_FAULT_ERRORS;
}