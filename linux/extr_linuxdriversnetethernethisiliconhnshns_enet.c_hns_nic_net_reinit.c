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
struct net_device {int dummy; } ;
struct hns_nic_priv {int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; TYPE_1__* ae_handle; } ;
typedef  enum hnae_port_type { ____Placeholder_hnae_port_type } hnae_port_type ;
struct TYPE_2__ {int port_type; } ;

/* Variables and functions */
 int HNAE_PORT_DEBUG ; 
 int /*<<< orphan*/  NIC_STATE_REINITING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_nic_net_down (struct net_device*) ; 
 int /*<<< orphan*/  hns_nic_net_reset (struct net_device*) ; 
 int /*<<< orphan*/  hns_nic_net_up (struct net_device*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void hns_nic_net_reinit(struct net_device *netdev)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);
	enum hnae_port_type type = priv->ae_handle->port_type;

	netif_trans_update(priv->netdev);
	while (test_and_set_bit(NIC_STATE_REINITING, &priv->state))
		usleep_range(1000, 2000);

	hns_nic_net_down(netdev);

	/* Only do hns_nic_net_reset in debug mode
	 * because of hardware limitation.
	 */
	if (type == HNAE_PORT_DEBUG)
		hns_nic_net_reset(netdev);

	(void)hns_nic_net_up(netdev);
	clear_bit(NIC_STATE_REINITING, &priv->state);
}