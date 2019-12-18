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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_dual_link; } ;

/* Variables and functions */
 struct intel_encoder* intel_get_lvds_encoder (struct drm_i915_private*) ; 
 TYPE_1__* to_lvds_encoder (int /*<<< orphan*/ *) ; 

bool intel_is_dual_link_lvds(struct drm_i915_private *dev_priv)
{
	struct intel_encoder *encoder = intel_get_lvds_encoder(dev_priv);

	return encoder && to_lvds_encoder(&encoder->base)->is_dual_link;
}