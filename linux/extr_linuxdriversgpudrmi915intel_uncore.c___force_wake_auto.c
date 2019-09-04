#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fw_domains; int fw_domains_active; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ___force_wake_auto (struct drm_i915_private*,int) ; 

__attribute__((used)) static inline void __force_wake_auto(struct drm_i915_private *dev_priv,
				     enum forcewake_domains fw_domains)
{
	if (WARN_ON(!fw_domains))
		return;

	/* Turn on all requested but inactive supported forcewake domains. */
	fw_domains &= dev_priv->uncore.fw_domains;
	fw_domains &= ~dev_priv->uncore.fw_domains_active;

	if (fw_domains)
		___force_wake_auto(dev_priv, fw_domains);
}