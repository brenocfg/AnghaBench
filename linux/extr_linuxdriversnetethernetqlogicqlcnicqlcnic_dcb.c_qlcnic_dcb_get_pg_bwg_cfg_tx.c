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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_dcb_pg_cfg {int /*<<< orphan*/  total_bw_percent; int /*<<< orphan*/  valid; } ;
struct qlcnic_dcb_cee {struct qlcnic_dcb_pg_cfg* pg_cfg; int /*<<< orphan*/  tc_param_valid; } ;
struct qlcnic_adapter {TYPE_2__* dcb; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_1__* cfg; } ;
struct TYPE_3__ {struct qlcnic_dcb_cee* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int QLC_DCB_MAX_PG ; 
 size_t QLC_DCB_OPER_IDX ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_dcb_get_pg_bwg_cfg_tx(struct net_device *netdev, int pgid,
					 u8 *bw_pct)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_pg_cfg *pgcfg;
	struct qlcnic_dcb_cee *type;

	*bw_pct = 0;
	type = &adapter->dcb->cfg->type[QLC_DCB_OPER_IDX];

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state) ||
	    !type->tc_param_valid)
		return;

	if (pgid < 0 || pgid >= QLC_DCB_MAX_PG)
		return;

	pgcfg = &type->pg_cfg[pgid];
	if (!pgcfg->valid)
		return;

	*bw_pct = pgcfg->total_bw_percent;
}