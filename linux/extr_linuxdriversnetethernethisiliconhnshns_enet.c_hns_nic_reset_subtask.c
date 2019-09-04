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
struct hns_nic_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; TYPE_1__* ae_handle; } ;
typedef  enum hnae_port_type { ____Placeholder_hnae_port_type } hnae_port_type ;
struct TYPE_2__ {int port_type; } ;

/* Variables and functions */
 int HNAE_PORT_DEBUG ; 
 int /*<<< orphan*/  NIC_STATE2_RESET_REQUESTED ; 
 int /*<<< orphan*/  NIC_STATE_DOWN ; 
 int /*<<< orphan*/  NIC_STATE_REMOVING ; 
 int /*<<< orphan*/  NIC_STATE_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_nic_dump (struct hns_nic_priv*) ; 
 int /*<<< orphan*/  hns_nic_net_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_nic_reset_subtask(struct hns_nic_priv *priv)
{
	enum hnae_port_type type = priv->ae_handle->port_type;

	if (!test_bit(NIC_STATE2_RESET_REQUESTED, &priv->state))
		return;
	clear_bit(NIC_STATE2_RESET_REQUESTED, &priv->state);

	/* If we're already down, removing or resetting, just bail */
	if (test_bit(NIC_STATE_DOWN, &priv->state) ||
	    test_bit(NIC_STATE_REMOVING, &priv->state) ||
	    test_bit(NIC_STATE_RESETTING, &priv->state))
		return;

	hns_nic_dump(priv);
	netdev_info(priv->netdev, "try to reset %s port!\n",
		    (type == HNAE_PORT_DEBUG ? "debug" : "service"));

	rtnl_lock();
	/* put off any impending NetWatchDogTimeout */
	netif_trans_update(priv->netdev);
	hns_nic_net_reinit(priv->netdev);

	rtnl_unlock();
}