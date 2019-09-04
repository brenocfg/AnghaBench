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
typedef  int u32 ;

/* Variables and functions */
 int DRM_MODE_PROP_ATOMIC ; 
 int DRM_MODE_PROP_EXTENDED_TYPE ; 
 int DRM_MODE_PROP_IMMUTABLE ; 
 int DRM_MODE_PROP_LEGACY_TYPE ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static bool drm_property_flags_valid(u32 flags)
{
	u32 legacy_type = flags & DRM_MODE_PROP_LEGACY_TYPE;
	u32 ext_type = flags & DRM_MODE_PROP_EXTENDED_TYPE;

	/* Reject undefined/deprecated flags */
	if (flags & ~(DRM_MODE_PROP_LEGACY_TYPE |
		      DRM_MODE_PROP_EXTENDED_TYPE |
		      DRM_MODE_PROP_IMMUTABLE |
		      DRM_MODE_PROP_ATOMIC))
		return false;

	/* We want either a legacy type or an extended type, but not both */
	if (!legacy_type == !ext_type)
		return false;

	/* Only one legacy type at a time please */
	if (legacy_type && !is_power_of_2(legacy_type))
		return false;

	return true;
}