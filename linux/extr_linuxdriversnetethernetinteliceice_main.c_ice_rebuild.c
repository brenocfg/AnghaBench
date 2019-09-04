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
struct ice_hw {int dummy; } ;
struct ice_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  flags; struct ice_hw hw; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  __ICE_RESET_FAILED ; 
 int /*<<< orphan*/  __ICE_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int ice_clear_pf_cfg (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_clear_pxe_mode (struct ice_hw*) ; 
 int ice_get_caps (struct ice_hw*) ; 
 int ice_init_all_ctrlq (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_pf_ena_all_vsi (struct ice_pf*) ; 
 int ice_req_irq_msix_misc (struct ice_pf*) ; 
 int ice_setup_pf_sw (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_shutdown_all_ctrlq (struct ice_hw*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_rebuild(struct ice_pf *pf)
{
	struct device *dev = &pf->pdev->dev;
	struct ice_hw *hw = &pf->hw;
	enum ice_status ret;
	int err;

	if (test_bit(__ICE_DOWN, pf->state))
		goto clear_recovery;

	dev_dbg(dev, "rebuilding pf\n");

	ret = ice_init_all_ctrlq(hw);
	if (ret) {
		dev_err(dev, "control queues init failed %d\n", ret);
		goto fail_reset;
	}

	ret = ice_clear_pf_cfg(hw);
	if (ret) {
		dev_err(dev, "clear PF configuration failed %d\n", ret);
		goto fail_reset;
	}

	ice_clear_pxe_mode(hw);

	ret = ice_get_caps(hw);
	if (ret) {
		dev_err(dev, "ice_get_caps failed %d\n", ret);
		goto fail_reset;
	}

	/* basic nic switch setup */
	err = ice_setup_pf_sw(pf);
	if (err) {
		dev_err(dev, "ice_setup_pf_sw failed\n");
		goto fail_reset;
	}

	/* start misc vector */
	if (test_bit(ICE_FLAG_MSIX_ENA, pf->flags)) {
		err = ice_req_irq_msix_misc(pf);
		if (err) {
			dev_err(dev, "misc vector setup failed: %d\n", err);
			goto fail_reset;
		}
	}

	/* restart the VSIs that were rebuilt and running before the reset */
	ice_pf_ena_all_vsi(pf);

	return;

fail_reset:
	ice_shutdown_all_ctrlq(hw);
	set_bit(__ICE_RESET_FAILED, pf->state);
clear_recovery:
	set_bit(__ICE_RESET_RECOVERY_PENDING, pf->state);
}