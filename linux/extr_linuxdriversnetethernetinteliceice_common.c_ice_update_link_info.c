#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int link_info; int /*<<< orphan*/  module_type; } ;
struct ice_phy_info {TYPE_1__ link_info; } ;
struct ice_port_info {struct ice_phy_info phy; struct ice_hw* hw; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_get_phy_caps_data {int /*<<< orphan*/  module_type; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_SW_CFG ; 
 int ICE_AQ_MEDIA_AVAILABLE ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_link_info (struct ice_port_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_aq_get_phy_caps (struct ice_port_info*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum ice_status
ice_update_link_info(struct ice_port_info *pi)
{
	struct ice_aqc_get_phy_caps_data *pcaps;
	struct ice_phy_info *phy_info;
	enum ice_status status;
	struct ice_hw *hw;

	if (!pi)
		return ICE_ERR_PARAM;

	hw = pi->hw;

	pcaps = devm_kzalloc(ice_hw_to_dev(hw), sizeof(*pcaps), GFP_KERNEL);
	if (!pcaps)
		return ICE_ERR_NO_MEMORY;

	phy_info = &pi->phy;
	status = ice_aq_get_link_info(pi, true, NULL, NULL);
	if (status)
		goto out;

	if (phy_info->link_info.link_info & ICE_AQ_MEDIA_AVAILABLE) {
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_SW_CFG,
					     pcaps, NULL);
		if (status)
			goto out;

		memcpy(phy_info->link_info.module_type, &pcaps->module_type,
		       sizeof(phy_info->link_info.module_type));
	}
out:
	devm_kfree(ice_hw_to_dev(hw), pcaps);
	return status;
}