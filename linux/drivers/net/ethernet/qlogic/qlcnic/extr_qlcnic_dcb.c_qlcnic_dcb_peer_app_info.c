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
typedef  scalar_t__ u16 ;
struct qlcnic_dcb_cee {TYPE_3__* app; } ;
struct qlcnic_adapter {TYPE_2__* dcb; } ;
struct net_device {int dummy; } ;
struct dcb_peer_app_info {int dummy; } ;
struct TYPE_6__ {scalar_t__ valid; } ;
struct TYPE_5__ {TYPE_1__* cfg; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {struct qlcnic_dcb_cee* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int QLC_DCB_MAX_APP ; 
 size_t QLC_DCB_PEER_IDX ; 
 int /*<<< orphan*/  memset (struct dcb_peer_app_info*,int /*<<< orphan*/ ,int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_dcb_peer_app_info(struct net_device *netdev,
				    struct dcb_peer_app_info *info,
				    u16 *app_count)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_cee *peer;
	int i;

	memset(info, 0, sizeof(*info));
	*app_count = 0;

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		return 0;

	peer = &adapter->dcb->cfg->type[QLC_DCB_PEER_IDX];

	for (i = 0; i < QLC_DCB_MAX_APP; i++) {
		if (peer->app[i].valid)
			(*app_count)++;
	}

	return 0;
}