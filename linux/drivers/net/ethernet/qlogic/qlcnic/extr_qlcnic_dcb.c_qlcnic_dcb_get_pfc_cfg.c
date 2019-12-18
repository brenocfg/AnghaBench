#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct qlcnic_dcb_tc_cfg {size_t up_tc_map; TYPE_3__* prio_cfg; int /*<<< orphan*/  valid; } ;
struct qlcnic_dcb_cee {struct qlcnic_dcb_tc_cfg* tc_cfg; int /*<<< orphan*/  pfc_mode_enable; } ;
struct qlcnic_adapter {TYPE_2__* dcb; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {size_t pfc_type; scalar_t__ valid; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; TYPE_1__* cfg; } ;
struct TYPE_4__ {struct qlcnic_dcb_cee* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 size_t QLC_DCB_GET_MAP (int) ; 
 size_t QLC_DCB_MAX_TC ; 
 size_t QLC_DCB_OPER_IDX ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_dcb_get_pfc_cfg(struct net_device *netdev, int prio,
				   u8 *setting)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_tc_cfg *tc_cfg;
	u8 val = QLC_DCB_GET_MAP(prio);
	struct qlcnic_dcb_cee *type;
	u8 i;

	*setting = 0;
	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state) ||
	    !type->pfc_mode_enable)
		return;

	for (i = 0; i < QLC_DCB_MAX_TC; i++) {
		tc_cfg = &type->tc_cfg[i];
		if (!tc_cfg->valid)
			continue;

		if ((val & tc_cfg->up_tc_map) && (tc_cfg->prio_cfg[prio].valid))
			*setting = tc_cfg->prio_cfg[prio].pfc_type;
	}
}