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
struct drm_i915_private {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  QUIRK_INCREASE_T12_DELAY ; 

__attribute__((used)) static void quirk_increase_t12_delay(struct drm_i915_private *i915)
{
	i915->quirks |= QUIRK_INCREASE_T12_DELAY;
	DRM_INFO("Applying T12 delay quirk\n");
}