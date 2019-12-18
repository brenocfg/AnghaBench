#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct hns_nic_priv {int /*<<< orphan*/  state; struct hnae_handle* ae_handle; } ;
struct hnae_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_STATE_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hnae_reinit_handle (struct hnae_handle*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void hns_nic_net_reset(struct net_device *ndev)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *handle = priv->ae_handle;

	while (test_and_set_bit(NIC_STATE_RESETTING, &priv->state))
		usleep_range(1000, 2000);

	(void)hnae_reinit_handle(handle);

	clear_bit(NIC_STATE_RESETTING, &priv->state);
}