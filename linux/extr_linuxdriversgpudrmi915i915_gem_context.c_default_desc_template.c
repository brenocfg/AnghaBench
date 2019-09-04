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
struct i915_hw_ppgtt {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int GEN8_CTX_ADDRESSING_MODE_SHIFT ; 
 int GEN8_CTX_L3LLC_COHERENT ; 
 int GEN8_CTX_PRIVILEGE ; 
 int GEN8_CTX_VALID ; 
 int INTEL_LEGACY_32B_CONTEXT ; 
 int INTEL_LEGACY_64B_CONTEXT ; 
 scalar_t__ IS_GEN8 (struct drm_i915_private const*) ; 
 scalar_t__ i915_vm_is_48bit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 default_desc_template(const struct drm_i915_private *i915,
				 const struct i915_hw_ppgtt *ppgtt)
{
	u32 address_mode;
	u32 desc;

	desc = GEN8_CTX_VALID | GEN8_CTX_PRIVILEGE;

	address_mode = INTEL_LEGACY_32B_CONTEXT;
	if (ppgtt && i915_vm_is_48bit(&ppgtt->vm))
		address_mode = INTEL_LEGACY_64B_CONTEXT;
	desc |= address_mode << GEN8_CTX_ADDRESSING_MODE_SHIFT;

	if (IS_GEN8(i915))
		desc |= GEN8_CTX_L3LLC_COHERENT;

	/* TODO: WaDisableLiteRestore when we start using semaphore
	 * signalling between Command Streamers
	 * ring->ctx_desc_template |= GEN8_CTX_FORCE_RESTORE;
	 */

	return desc;
}