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
struct sun8i_hdmi_phy_variant {int /*<<< orphan*/  phy_cfg; int /*<<< orphan*/  cur_ctr; int /*<<< orphan*/  mpll_cfg; scalar_t__ is_custom_phy; } ;
struct sun8i_hdmi_phy {struct sun8i_hdmi_phy_variant* variant; } ;
struct dw_hdmi_plat_data {char* phy_name; int /*<<< orphan*/  phy_config; int /*<<< orphan*/  cur_ctr; int /*<<< orphan*/  mpll_cfg; struct sun8i_hdmi_phy* phy_data; int /*<<< orphan*/ * phy_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  sun8i_hdmi_phy_ops ; 

void sun8i_hdmi_phy_set_ops(struct sun8i_hdmi_phy *phy,
			    struct dw_hdmi_plat_data *plat_data)
{
	struct sun8i_hdmi_phy_variant *variant = phy->variant;

	if (variant->is_custom_phy) {
		plat_data->phy_ops = &sun8i_hdmi_phy_ops;
		plat_data->phy_name = "sun8i_dw_hdmi_phy";
		plat_data->phy_data = phy;
	} else {
		plat_data->mpll_cfg = variant->mpll_cfg;
		plat_data->cur_ctr = variant->cur_ctr;
		plat_data->phy_config = variant->phy_cfg;
	}
}