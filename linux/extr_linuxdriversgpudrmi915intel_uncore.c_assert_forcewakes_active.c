#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  force_wake_get; } ;
struct TYPE_4__ {int fw_domains; int fw_domains_active; TYPE_1__ funcs; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct drm_i915_private*) ; 

void assert_forcewakes_active(struct drm_i915_private *dev_priv,
			      enum forcewake_domains fw_domains)
{
	if (!dev_priv->uncore.funcs.force_wake_get)
		return;

	assert_rpm_wakelock_held(dev_priv);

	fw_domains &= dev_priv->uncore.fw_domains;
	WARN(fw_domains & ~dev_priv->uncore.fw_domains_active,
	     "Expected %08x fw_domains to be active, but %08x are off\n",
	     fw_domains, fw_domains & ~dev_priv->uncore.fw_domains_active);
}