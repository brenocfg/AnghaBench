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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASLC_ALS_ILLUM_FAILED ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 

__attribute__((used)) static u32 asle_set_als_illum(struct drm_i915_private *dev_priv, u32 alsi)
{
	/* alsi is the current ALS reading in lux. 0 indicates below sensor
	   range, 0xffff indicates above sensor range. 1-0xfffe are valid */
	DRM_DEBUG_DRIVER("Illum is not supported\n");
	return ASLC_ALS_ILLUM_FAILED;
}