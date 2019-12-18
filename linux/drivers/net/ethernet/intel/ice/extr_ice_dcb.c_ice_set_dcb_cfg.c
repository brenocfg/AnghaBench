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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_dcbx_cfg {scalar_t__ app_mode; } ;
struct ice_port_info {struct ice_dcbx_cfg local_dcbx_cfg; struct ice_hw* hw; } ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ICE_DCBX_APPS_NON_WILLING ; 
 int ICE_ERR_NO_MEMORY ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ICE_LLDPDU_SIZE ; 
 int /*<<< orphan*/  SET_LOCAL_MIB_TYPE_CEE_NON_WILLING ; 
 int /*<<< orphan*/  SET_LOCAL_MIB_TYPE_LOCAL_MIB ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_aq_set_lldp_mib (struct ice_hw*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_dcb_cfg_to_lldp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ice_dcbx_cfg*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

enum ice_status ice_set_dcb_cfg(struct ice_port_info *pi)
{
	u8 mib_type, *lldpmib = NULL;
	struct ice_dcbx_cfg *dcbcfg;
	enum ice_status ret;
	struct ice_hw *hw;
	u16 miblen;

	if (!pi)
		return ICE_ERR_PARAM;

	hw = pi->hw;

	/* update the HW local config */
	dcbcfg = &pi->local_dcbx_cfg;
	/* Allocate the LLDPDU */
	lldpmib = devm_kzalloc(ice_hw_to_dev(hw), ICE_LLDPDU_SIZE, GFP_KERNEL);
	if (!lldpmib)
		return ICE_ERR_NO_MEMORY;

	mib_type = SET_LOCAL_MIB_TYPE_LOCAL_MIB;
	if (dcbcfg->app_mode == ICE_DCBX_APPS_NON_WILLING)
		mib_type |= SET_LOCAL_MIB_TYPE_CEE_NON_WILLING;

	ice_dcb_cfg_to_lldp(lldpmib, &miblen, dcbcfg);
	ret = ice_aq_set_lldp_mib(hw, mib_type, (void *)lldpmib, miblen,
				  NULL);

	devm_kfree(ice_hw_to_dev(hw), lldpmib);

	return ret;
}