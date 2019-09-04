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
 int /*<<< orphan*/  GFX_FLSH_CNTL_EN ; 
 int /*<<< orphan*/  GFX_FLSH_CNTL_GEN6 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmio_hw_access_post (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mmio_hw_access_pre (struct drm_i915_private*) ; 

__attribute__((used)) static void ggtt_invalidate(struct drm_i915_private *dev_priv)
{
	mmio_hw_access_pre(dev_priv);
	I915_WRITE(GFX_FLSH_CNTL_GEN6, GFX_FLSH_CNTL_EN);
	mmio_hw_access_post(dev_priv);
}