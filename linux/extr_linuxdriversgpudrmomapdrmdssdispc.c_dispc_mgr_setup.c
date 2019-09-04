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
struct dispc_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  FEAT_CPR ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_alpha_fixed_zorder (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_cpr (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_trans_key (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_cpr_coef (struct dispc_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispc_mgr_set_default_color (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_trans_key (struct dispc_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_setup(struct dispc_device *dispc,
			    enum omap_channel channel,
			    const struct omap_overlay_manager_info *info)
{
	dispc_mgr_set_default_color(dispc, channel, info->default_color);
	dispc_mgr_set_trans_key(dispc, channel, info->trans_key_type,
				info->trans_key);
	dispc_mgr_enable_trans_key(dispc, channel, info->trans_enabled);
	dispc_mgr_enable_alpha_fixed_zorder(dispc, channel,
			info->partial_alpha_enabled);
	if (dispc_has_feature(dispc, FEAT_CPR)) {
		dispc_mgr_enable_cpr(dispc, channel, info->cpr_enable);
		dispc_mgr_set_cpr_coef(dispc, channel, &info->cpr_coefs);
	}
}