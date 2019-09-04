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
typedef  size_t u8 ;
struct qlcnic_dcb_tc_cfg {int /*<<< orphan*/  up_tc_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_pfc_tc; } ;
struct qlcnic_dcb_cfg {TYPE_2__ capability; struct qlcnic_dcb_cee* type; } ;
struct qlcnic_dcb_cee {struct qlcnic_dcb_tc_cfg* tc_cfg; } ;
struct qlcnic_adapter {TYPE_1__* dcb; } ;
struct net_device {int dummy; } ;
struct cee_pfc {int /*<<< orphan*/  tcs_supported; int /*<<< orphan*/  pfc_en; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; struct qlcnic_dcb_cfg* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int /*<<< orphan*/  QLC_DCB_GET_MAP (size_t) ; 
 size_t QLC_DCB_MAX_TC ; 
 size_t QLC_DCB_PEER_IDX ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_dcb_get_pfc_cfg (struct net_device*,size_t,size_t*) ; 
 size_t qlcnic_dcb_prio_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_dcb_cee_peer_get_pfc(struct net_device *netdev,
				       struct cee_pfc *pfc)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_cfg *cfg = adapter->dcb->cfg;
	struct qlcnic_dcb_tc_cfg *tc;
	struct qlcnic_dcb_cee *peer;
	u8 i, setting, prio;

	pfc->pfc_en = 0;

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		return 0;

	peer = &cfg->type[QLC_DCB_PEER_IDX];

	for (i = 0; i < QLC_DCB_MAX_TC; i++) {
		tc = &peer->tc_cfg[i];
		prio = qlcnic_dcb_prio_count(tc->up_tc_map);

		setting = 0;
		qlcnic_dcb_get_pfc_cfg(netdev, prio, &setting);
		if (setting)
			pfc->pfc_en |= QLC_DCB_GET_MAP(i);
	}

	pfc->tcs_supported = cfg->capability.max_pfc_tc;

	return 0;
}