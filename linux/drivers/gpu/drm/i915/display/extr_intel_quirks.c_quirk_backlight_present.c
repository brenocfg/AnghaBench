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
 int /*<<< orphan*/  QUIRK_BACKLIGHT_PRESENT ; 

__attribute__((used)) static void quirk_backlight_present(struct drm_i915_private *i915)
{
	i915->quirks |= QUIRK_BACKLIGHT_PRESENT;
	DRM_INFO("applying backlight present quirk\n");
}