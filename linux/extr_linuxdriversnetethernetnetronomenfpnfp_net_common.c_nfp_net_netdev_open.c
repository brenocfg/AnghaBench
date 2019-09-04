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
struct TYPE_2__ {int /*<<< orphan*/  num_rx_rings; int /*<<< orphan*/  num_stack_tx_rings; } ;
struct nfp_net {TYPE_1__ dp; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_close_free_all (struct nfp_net*) ; 
 int nfp_net_open_alloc_all (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_open_stack (struct nfp_net*) ; 
 int nfp_net_set_config_and_enable (struct nfp_net*) ; 
 int nfp_port_configure (struct net_device*,int) ; 

__attribute__((used)) static int nfp_net_netdev_open(struct net_device *netdev)
{
	struct nfp_net *nn = netdev_priv(netdev);
	int err;

	/* Step 1: Allocate resources for rings and the like
	 * - Request interrupts
	 * - Allocate RX and TX ring resources
	 * - Setup initial RSS table
	 */
	err = nfp_net_open_alloc_all(nn);
	if (err)
		return err;

	err = netif_set_real_num_tx_queues(netdev, nn->dp.num_stack_tx_rings);
	if (err)
		goto err_free_all;

	err = netif_set_real_num_rx_queues(netdev, nn->dp.num_rx_rings);
	if (err)
		goto err_free_all;

	/* Step 2: Configure the NFP
	 * - Ifup the physical interface if it exists
	 * - Enable rings from 0 to tx_rings/rx_rings - 1.
	 * - Write MAC address (in case it changed)
	 * - Set the MTU
	 * - Set the Freelist buffer size
	 * - Enable the FW
	 */
	err = nfp_port_configure(netdev, true);
	if (err)
		goto err_free_all;

	err = nfp_net_set_config_and_enable(nn);
	if (err)
		goto err_port_disable;

	/* Step 3: Enable for kernel
	 * - put some freelist descriptors on each RX ring
	 * - enable NAPI on each ring
	 * - enable all TX queues
	 * - set link state
	 */
	nfp_net_open_stack(nn);

	return 0;

err_port_disable:
	nfp_port_configure(netdev, false);
err_free_all:
	nfp_net_close_free_all(nn);
	return err;
}