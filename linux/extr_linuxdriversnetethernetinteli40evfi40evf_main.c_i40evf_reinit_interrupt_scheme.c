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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct i40evf_adapter {int /*<<< orphan*/  aq_required; TYPE_1__ vsi; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40EVF_FLAG_AQ_CONFIGURE_RSS ; 
 scalar_t__ RSS_AQ (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  i40evf_free_misc_irq (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_q_vectors (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_queues (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_traffic_irqs (struct i40evf_adapter*) ; 
 int i40evf_init_interrupt_scheme (struct i40evf_adapter*) ; 
 int i40evf_init_rss (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_map_rings_to_vectors (struct i40evf_adapter*) ; 
 int i40evf_request_misc_irq (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_reset_interrupt_capability (struct i40evf_adapter*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40evf_reinit_interrupt_scheme(struct i40evf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err;

	if (netif_running(netdev))
		i40evf_free_traffic_irqs(adapter);
	i40evf_free_misc_irq(adapter);
	i40evf_reset_interrupt_capability(adapter);
	i40evf_free_q_vectors(adapter);
	i40evf_free_queues(adapter);

	err =  i40evf_init_interrupt_scheme(adapter);
	if (err)
		goto err;

	netif_tx_stop_all_queues(netdev);

	err = i40evf_request_misc_irq(adapter);
	if (err)
		goto err;

	set_bit(__I40E_VSI_DOWN, adapter->vsi.state);

	i40evf_map_rings_to_vectors(adapter);

	if (RSS_AQ(adapter))
		adapter->aq_required |= I40EVF_FLAG_AQ_CONFIGURE_RSS;
	else
		err = i40evf_init_rss(adapter);
err:
	return err;
}