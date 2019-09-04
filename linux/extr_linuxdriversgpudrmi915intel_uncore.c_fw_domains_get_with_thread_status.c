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
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  __gen6_gt_wait_for_thread_c0 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  fw_domains_get (struct drm_i915_private*,int) ; 

__attribute__((used)) static void fw_domains_get_with_thread_status(struct drm_i915_private *dev_priv,
					      enum forcewake_domains fw_domains)
{
	fw_domains_get(dev_priv, fw_domains);

	/* WaRsForcewakeWaitTC0:snb,ivb,hsw,bdw,vlv */
	__gen6_gt_wait_for_thread_c0(dev_priv);
}