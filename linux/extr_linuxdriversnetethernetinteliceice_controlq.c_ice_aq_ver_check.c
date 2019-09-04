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
struct ice_hw {scalar_t__ api_maj_ver; scalar_t__ api_min_ver; } ;

/* Variables and functions */
 scalar_t__ EXP_FW_API_VER_MAJOR ; 
 scalar_t__ EXP_FW_API_VER_MINOR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static bool ice_aq_ver_check(struct ice_hw *hw)
{
	if (hw->api_maj_ver > EXP_FW_API_VER_MAJOR) {
		/* Major API version is newer than expected, don't load */
		dev_warn(ice_hw_to_dev(hw),
			 "The driver for the device stopped because the NVM image is newer than expected. You must install the most recent version of the network driver.\n");
		return false;
	} else if (hw->api_maj_ver == EXP_FW_API_VER_MAJOR) {
		if (hw->api_min_ver > (EXP_FW_API_VER_MINOR + 2))
			dev_info(ice_hw_to_dev(hw),
				 "The driver for the device detected a newer version of the NVM image than expected. Please install the most recent version of the network driver.\n");
		else if ((hw->api_min_ver + 2) < EXP_FW_API_VER_MINOR)
			dev_info(ice_hw_to_dev(hw),
				 "The driver for the device detected an older version of the NVM image than expected. Please update the NVM image.\n");
	} else {
		/* Major API version is older than expected, log a warning */
		dev_info(ice_hw_to_dev(hw),
			 "The driver for the device detected an older version of the NVM image than expected. Please update the NVM image.\n");
	}
	return true;
}