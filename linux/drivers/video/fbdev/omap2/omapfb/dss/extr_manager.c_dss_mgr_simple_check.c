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
struct omap_overlay_manager_info {scalar_t__ trans_key_type; scalar_t__ trans_enabled; scalar_t__ partial_alpha_enabled; } ;
struct omap_overlay_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FEAT_ALPHA_FIXED_ZORDER ; 
 scalar_t__ OMAP_DSS_COLOR_KEY_GFX_DST ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

int dss_mgr_simple_check(struct omap_overlay_manager *mgr,
		const struct omap_overlay_manager_info *info)
{
	if (dss_has_feature(FEAT_ALPHA_FIXED_ZORDER)) {
		/*
		 * OMAP3 supports only graphics source transparency color key
		 * and alpha blending simultaneously. See TRM 15.4.2.4.2.2
		 * Alpha Mode.
		 */
		if (info->partial_alpha_enabled && info->trans_enabled
			&& info->trans_key_type != OMAP_DSS_COLOR_KEY_GFX_DST) {
			DSSERR("check_manager: illegal transparency key\n");
			return -EINVAL;
		}
	}

	return 0;
}