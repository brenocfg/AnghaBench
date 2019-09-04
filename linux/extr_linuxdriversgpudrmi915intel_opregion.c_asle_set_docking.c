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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ASLC_DOCKING_FAILED ; 
 int ASLE_IUER_DOCKING ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 

__attribute__((used)) static u32 asle_set_docking(struct drm_i915_private *dev_priv, u32 iuer)
{
	if (iuer & ASLE_IUER_DOCKING)
		DRM_DEBUG_DRIVER("Docking is not supported (docked)\n");
	else
		DRM_DEBUG_DRIVER("Docking is not supported (undocked)\n");

	return ASLC_DOCKING_FAILED;
}