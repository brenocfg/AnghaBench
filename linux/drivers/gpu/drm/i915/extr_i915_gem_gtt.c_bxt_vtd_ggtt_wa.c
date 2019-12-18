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
struct i915_address_space {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_FLSH_CNTL_GEN6 ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_vtd_ggtt_wa(struct i915_address_space *vm)
{
	struct drm_i915_private *dev_priv = vm->i915;

	/*
	 * Make sure the internal GAM fifo has been cleared of all GTT
	 * writes before exiting stop_machine(). This guarantees that
	 * any aperture accesses waiting to start in another process
	 * cannot back up behind the GTT writes causing a hang.
	 * The register can be any arbitrary GAM register.
	 */
	POSTING_READ(GFX_FLSH_CNTL_GEN6);
}