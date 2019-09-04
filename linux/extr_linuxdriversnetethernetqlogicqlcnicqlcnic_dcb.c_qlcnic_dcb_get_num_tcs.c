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
struct TYPE_4__ {int /*<<< orphan*/  max_pfc_tc; int /*<<< orphan*/  max_ets_tc; } ;
struct qlcnic_dcb_cfg {TYPE_2__ capability; } ;
struct qlcnic_adapter {TYPE_1__* dcb; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; struct qlcnic_dcb_cfg* cfg; } ;

/* Variables and functions */
#define  DCB_NUMTCS_ATTR_PFC 129 
#define  DCB_NUMTCS_ATTR_PG 128 
 int EINVAL ; 
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_dcb_get_num_tcs(struct net_device *netdev, int attr, u8 *num)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_cfg *cfg = adapter->dcb->cfg;

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		return -EINVAL;

	switch (attr) {
	case DCB_NUMTCS_ATTR_PG:
		*num = cfg->capability.max_ets_tc;
		return 0;
	case DCB_NUMTCS_ATTR_PFC:
		*num = cfg->capability.max_pfc_tc;
		return 0;
	default:
		return -EINVAL;
	}
}