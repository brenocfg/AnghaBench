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
struct omap_overlay_manager_info {int /*<<< orphan*/  cpr_coefs; int /*<<< orphan*/  cpr_enable; int /*<<< orphan*/  partial_alpha_enabled; int /*<<< orphan*/  trans_enabled; int /*<<< orphan*/  trans_key; int /*<<< orphan*/  trans_key_type; int /*<<< orphan*/  default_color; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  FEAT_CPR ; 
 int /*<<< orphan*/  dispc_mgr_enable_alpha_fixed_zorder (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_cpr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_trans_key (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_cpr_coef (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispc_mgr_set_default_color (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_trans_key (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

void dispc_mgr_setup(enum omap_channel channel,
		const struct omap_overlay_manager_info *info)
{
	dispc_mgr_set_default_color(channel, info->default_color);
	dispc_mgr_set_trans_key(channel, info->trans_key_type, info->trans_key);
	dispc_mgr_enable_trans_key(channel, info->trans_enabled);
	dispc_mgr_enable_alpha_fixed_zorder(channel,
			info->partial_alpha_enabled);
	if (dss_has_feature(FEAT_CPR)) {
		dispc_mgr_enable_cpr(channel, info->cpr_enable);
		dispc_mgr_set_cpr_coef(channel, &info->cpr_coefs);
	}
}