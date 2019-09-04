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
struct tc_cbs_qopt_offload {int queue; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; int /*<<< orphan*/  sendslope; int /*<<< orphan*/  idleslope; int /*<<< orphan*/  enable; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  igb_offload_apply (struct igb_adapter*,int) ; 
 int igb_save_cbs_params (struct igb_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_offload_cbs(struct igb_adapter *adapter,
			   struct tc_cbs_qopt_offload *qopt)
{
	struct e1000_hw *hw = &adapter->hw;
	int err;

	/* CBS offloading is only supported by i210 controller. */
	if (hw->mac.type != e1000_i210)
		return -EOPNOTSUPP;

	/* CBS offloading is only supported by queue 0 and queue 1. */
	if (qopt->queue < 0 || qopt->queue > 1)
		return -EINVAL;

	err = igb_save_cbs_params(adapter, qopt->queue, qopt->enable,
				  qopt->idleslope, qopt->sendslope,
				  qopt->hicredit, qopt->locredit);
	if (err)
		return err;

	igb_offload_apply(adapter, qopt->queue);

	return 0;
}