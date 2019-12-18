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
struct ice_hw {int dummy; } ;
struct ice_dcbx_cfg {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  ICE_LLDPDU_SIZE ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_aq_get_lldp_mib (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int ice_lldp_to_dcb_cfg (int /*<<< orphan*/ *,struct ice_dcbx_cfg*) ; 

enum ice_status
ice_aq_get_dcb_cfg(struct ice_hw *hw, u8 mib_type, u8 bridgetype,
		   struct ice_dcbx_cfg *dcbcfg)
{
	enum ice_status ret;
	u8 *lldpmib;

	/* Allocate the LLDPDU */
	lldpmib = devm_kzalloc(ice_hw_to_dev(hw), ICE_LLDPDU_SIZE, GFP_KERNEL);
	if (!lldpmib)
		return ICE_ERR_NO_MEMORY;

	ret = ice_aq_get_lldp_mib(hw, bridgetype, mib_type, (void *)lldpmib,
				  ICE_LLDPDU_SIZE, NULL, NULL, NULL);

	if (!ret)
		/* Parse LLDP MIB to get DCB configuration */
		ret = ice_lldp_to_dcb_cfg(lldpmib, dcbcfg);

	devm_kfree(ice_hw_to_dev(hw), lldpmib);

	return ret;
}