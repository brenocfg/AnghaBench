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
struct ice_hw {int /*<<< orphan*/  pkg_size; scalar_t__ pkg_copy; } ;
struct ice_pf {int /*<<< orphan*/  flags; struct ice_hw hw; TYPE_1__* pdev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ICE_FLAG_ADV_FEATURES ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int ice_copy_and_init_pkg (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_init_pkg (struct ice_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_log_pkg_init (struct ice_hw*,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_load_pkg(const struct firmware *firmware, struct ice_pf *pf)
{
	enum ice_status status = ICE_ERR_PARAM;
	struct device *dev = &pf->pdev->dev;
	struct ice_hw *hw = &pf->hw;

	/* Load DDP Package */
	if (firmware && !hw->pkg_copy) {
		status = ice_copy_and_init_pkg(hw, firmware->data,
					       firmware->size);
		ice_log_pkg_init(hw, &status);
	} else if (!firmware && hw->pkg_copy) {
		/* Reload package during rebuild after CORER/GLOBR reset */
		status = ice_init_pkg(hw, hw->pkg_copy, hw->pkg_size);
		ice_log_pkg_init(hw, &status);
	} else {
		dev_err(dev,
			"The DDP package file failed to load. Entering Safe Mode.\n");
	}

	if (status) {
		/* Safe Mode */
		clear_bit(ICE_FLAG_ADV_FEATURES, pf->flags);
		return;
	}

	/* Successful download package is the precondition for advanced
	 * features, hence setting the ICE_FLAG_ADV_FEATURES flag
	 */
	set_bit(ICE_FLAG_ADV_FEATURES, pf->flags);
}