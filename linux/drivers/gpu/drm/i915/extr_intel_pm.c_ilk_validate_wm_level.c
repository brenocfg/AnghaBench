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
struct intel_wm_level {int enable; scalar_t__ pri_val; scalar_t__ spr_val; scalar_t__ cur_val; } ;
struct ilk_wm_maximums {scalar_t__ pri; scalar_t__ spr; scalar_t__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,scalar_t__,scalar_t__) ; 
 void* min_t (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static bool ilk_validate_wm_level(int level,
				  const struct ilk_wm_maximums *max,
				  struct intel_wm_level *result)
{
	bool ret;

	/* already determined to be invalid? */
	if (!result->enable)
		return false;

	result->enable = result->pri_val <= max->pri &&
			 result->spr_val <= max->spr &&
			 result->cur_val <= max->cur;

	ret = result->enable;

	/*
	 * HACK until we can pre-compute everything,
	 * and thus fail gracefully if LP0 watermarks
	 * are exceeded...
	 */
	if (level == 0 && !result->enable) {
		if (result->pri_val > max->pri)
			DRM_DEBUG_KMS("Primary WM%d too large %u (max %u)\n",
				      level, result->pri_val, max->pri);
		if (result->spr_val > max->spr)
			DRM_DEBUG_KMS("Sprite WM%d too large %u (max %u)\n",
				      level, result->spr_val, max->spr);
		if (result->cur_val > max->cur)
			DRM_DEBUG_KMS("Cursor WM%d too large %u (max %u)\n",
				      level, result->cur_val, max->cur);

		result->pri_val = min_t(u32, result->pri_val, max->pri);
		result->spr_val = min_t(u32, result->spr_val, max->spr);
		result->cur_val = min_t(u32, result->cur_val, max->cur);
		result->enable = true;
	}

	return ret;
}