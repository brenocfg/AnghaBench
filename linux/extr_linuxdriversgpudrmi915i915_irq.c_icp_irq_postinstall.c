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
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDEIER ; 
 int /*<<< orphan*/  SDEIIR ; 
 int /*<<< orphan*/  SDEIMR ; 
 int SDE_GMBUS_ICP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gen3_assert_iir_is_zero (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icp_hpd_detection_setup (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void icp_irq_postinstall(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 mask = SDE_GMBUS_ICP;

	WARN_ON(I915_READ(SDEIER) != 0);
	I915_WRITE(SDEIER, 0xffffffff);
	POSTING_READ(SDEIER);

	gen3_assert_iir_is_zero(dev_priv, SDEIIR);
	I915_WRITE(SDEIMR, ~mask);

	icp_hpd_detection_setup(dev_priv);
}