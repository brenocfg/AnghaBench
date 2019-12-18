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
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {scalar_t__ has_reset_engine; } ;
struct TYPE_3__ {int reset; } ;

/* Variables and functions */
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 TYPE_1__ i915_modparams ; 

bool intel_has_reset_engine(struct drm_i915_private *i915)
{
	return INTEL_INFO(i915)->has_reset_engine && i915_modparams.reset >= 2;
}