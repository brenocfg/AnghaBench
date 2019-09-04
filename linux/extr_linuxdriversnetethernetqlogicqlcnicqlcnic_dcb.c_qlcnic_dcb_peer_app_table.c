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
struct qlcnic_dcb_cee {struct qlcnic_dcb_app* app; } ;
struct qlcnic_dcb_app {int /*<<< orphan*/  protocol; int /*<<< orphan*/  priority; int /*<<< orphan*/  selector; int /*<<< orphan*/  valid; } ;
struct qlcnic_adapter {TYPE_2__* dcb; } ;
struct net_device {int dummy; } ;
struct dcb_app {int /*<<< orphan*/  protocol; int /*<<< orphan*/  priority; int /*<<< orphan*/  selector; } ;
struct TYPE_4__ {TYPE_1__* cfg; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct qlcnic_dcb_cee* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int QLC_DCB_MAX_APP ; 
 size_t QLC_DCB_PEER_IDX ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_dcb_peer_app_table(struct net_device *netdev,
				     struct dcb_app *table)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_dcb_cee *peer;
	struct qlcnic_dcb_app *app;
	int i, j;

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		return 0;

	peer = &adapter->dcb->cfg->type[QLC_DCB_PEER_IDX];

	for (i = 0, j = 0; i < QLC_DCB_MAX_APP; i++) {
		app = &peer->app[i];
		if (!app->valid)
			continue;

		table[j].selector = app->selector;
		table[j].priority = app->priority;
		table[j++].protocol = app->protocol;
	}

	return 0;
}