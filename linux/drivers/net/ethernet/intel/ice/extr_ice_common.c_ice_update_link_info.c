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
struct ice_link_status {int link_info; int /*<<< orphan*/  module_type; } ;
struct TYPE_2__ {struct ice_link_status link_info; } ;
struct ice_port_info {struct ice_hw* hw; TYPE_1__ phy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_get_phy_caps_data {int /*<<< orphan*/  module_type; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQC_REPORT_TOPO_CAP ; 
 int ICE_AQ_MEDIA_AVAILABLE ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*) ; 
 struct ice_aqc_get_phy_caps_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_link_info (struct ice_port_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_aq_get_phy_caps (struct ice_port_info*,int,int /*<<< orphan*/ ,struct ice_aqc_get_phy_caps_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

enum ice_status ice_update_link_info(struct ice_port_info *pi)
{
	struct ice_link_status *li;
	enum ice_status status;

	if (!pi)
		return ICE_ERR_PARAM;

	li = &pi->phy.link_info;

	status = ice_aq_get_link_info(pi, true, NULL, NULL);
	if (status)
		return status;

	if (li->link_info & ICE_AQ_MEDIA_AVAILABLE) {
		struct ice_aqc_get_phy_caps_data *pcaps;
		struct ice_hw *hw;

		hw = pi->hw;
		pcaps = devm_kzalloc(ice_hw_to_dev(hw), sizeof(*pcaps),
				     GFP_KERNEL);
		if (!pcaps)
			return ICE_ERR_NO_MEMORY;

		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP,
					     pcaps, NULL);
		if (!status)
			memcpy(li->module_type, &pcaps->module_type,
			       sizeof(li->module_type));

		devm_kfree(ice_hw_to_dev(hw), pcaps);
	}

	return status;
}