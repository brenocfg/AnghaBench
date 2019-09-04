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
struct TYPE_2__ {int /*<<< orphan*/  (* init_clock_gating ) (struct drm_i915_private*) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 

void intel_init_clock_gating(struct drm_i915_private *dev_priv)
{
	dev_priv->display.init_clock_gating(dev_priv);
}