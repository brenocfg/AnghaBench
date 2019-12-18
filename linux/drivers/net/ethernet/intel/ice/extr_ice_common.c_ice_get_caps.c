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
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ice_aqc_opc_list_dev_caps ; 
 int /*<<< orphan*/  ice_aqc_opc_list_func_caps ; 
 int ice_discover_caps (struct ice_hw*,int /*<<< orphan*/ ) ; 

enum ice_status ice_get_caps(struct ice_hw *hw)
{
	enum ice_status status;

	status = ice_discover_caps(hw, ice_aqc_opc_list_dev_caps);
	if (!status)
		status = ice_discover_caps(hw, ice_aqc_opc_list_func_caps);

	return status;
}