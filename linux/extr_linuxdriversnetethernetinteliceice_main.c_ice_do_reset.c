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
struct ice_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  pfr_count; struct ice_hw hw; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  enum ice_reset_req { ____Placeholder_ice_reset_req } ice_reset_req ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ICE_RESET_PFR ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ICE_RESET_FAILED ; 
 int /*<<< orphan*/  __ICE_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  ice_prepare_for_reset (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_rebuild (struct ice_pf*) ; 
 scalar_t__ ice_reset (struct ice_hw*,int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_do_reset(struct ice_pf *pf, enum ice_reset_req reset_type)
{
	struct device *dev = &pf->pdev->dev;
	struct ice_hw *hw = &pf->hw;

	dev_dbg(dev, "reset_type 0x%x requested\n", reset_type);
	WARN_ON(in_interrupt());

	/* PFR is a bit of a special case because it doesn't result in an OICR
	 * interrupt. So for PFR, we prepare for reset, issue the reset and
	 * rebuild sequentially.
	 */
	if (reset_type == ICE_RESET_PFR) {
		set_bit(__ICE_RESET_RECOVERY_PENDING, pf->state);
		ice_prepare_for_reset(pf);
	}

	/* trigger the reset */
	if (ice_reset(hw, reset_type)) {
		dev_err(dev, "reset %d failed\n", reset_type);
		set_bit(__ICE_RESET_FAILED, pf->state);
		clear_bit(__ICE_RESET_RECOVERY_PENDING, pf->state);
		return;
	}

	if (reset_type == ICE_RESET_PFR) {
		pf->pfr_count++;
		ice_rebuild(pf);
		clear_bit(__ICE_RESET_RECOVERY_PENDING, pf->state);
	}
}