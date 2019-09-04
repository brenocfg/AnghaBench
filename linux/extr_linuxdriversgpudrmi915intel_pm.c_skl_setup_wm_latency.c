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
struct TYPE_2__ {int /*<<< orphan*/  skl_latency; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_print_wm_latency (struct drm_i915_private*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_read_wm_latency (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_setup_wm_latency(struct drm_i915_private *dev_priv)
{
	intel_read_wm_latency(dev_priv, dev_priv->wm.skl_latency);
	intel_print_wm_latency(dev_priv, "Gen9 Plane", dev_priv->wm.skl_latency);
}