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
struct TYPE_4__ {int /*<<< orphan*/  fw_domains_active; TYPE_1__ funcs; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void assert_forcewakes_inactive(struct drm_i915_private *dev_priv)
{
	if (!dev_priv->uncore.funcs.force_wake_get)
		return;

	WARN(dev_priv->uncore.fw_domains_active,
	     "Expected all fw_domains to be inactive, but %08x are still on\n",
	     dev_priv->uncore.fw_domains_active);
}