#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qlcnic_dcb_tc_cfg {int pgid; int prio_type; int up_tc_map; int bwg_percent; scalar_t__ valid; } ;
struct qlcnic_dcb_cee {struct qlcnic_dcb_tc_cfg* tc_cfg; int /*<<< orphan*/  tc_param_valid; } ;
struct qlcnic_adapter {TYPE_2__* dcb; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_1__* cfg; } ;
struct TYPE_3__ {struct qlcnic_dcb_cee* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int QLC_DCB_MAX_TC ; 
 size_t QLC_DCB_OPER_IDX ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlcnic_dcb_get_pg_tc_cfg_tx(struct net_device *netdev, int tc, u8 *prio,
			    u8 *pgid, u8 *bw_per, u8 *up_tc_map)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_tc_cfg *tc_cfg, *temp;
	struct qlcnic_dcb_cee *type;
	u8 i, cnt, pg;

	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];
	*prio = *pgid = *bw_per = *up_tc_map = 0;

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state) ||
	    !type->tc_param_valid)
		return;

	if (tc < 0 || (tc >= QLC_DCB_MAX_TC))
		return;

	tc_cfg = &type->tc_cfg[tc];
	if (!tc_cfg->valid)
		return;

	*pgid = tc_cfg->pgid;
	*prio = tc_cfg->prio_type;
	*up_tc_map = tc_cfg->up_tc_map;
	pg = *pgid;

	for (i = 0, cnt = 0; i < QLC_DCB_MAX_TC; i++) {
		temp = &type->tc_cfg[i];
		if (temp->valid && (pg == temp->pgid))
			cnt++;
	}

	tc_cfg->bwg_percent = (100 / cnt);
	*bw_per = tc_cfg->bwg_percent;
}