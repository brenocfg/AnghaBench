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
struct nfp_net {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_net_clear_config_and_disable (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_close_free_all (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_close_stack (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_port_configure (struct net_device*,int) ; 
 int /*<<< orphan*/  nn_dbg (struct nfp_net*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_net_netdev_close(struct net_device *netdev)
{
	struct nfp_net *nn = netdev_priv(netdev);

	/* Step 1: Disable RX and TX rings from the Linux kernel perspective
	 */
	nfp_net_close_stack(nn);

	/* Step 2: Tell NFP
	 */
	nfp_net_clear_config_and_disable(nn);
	nfp_port_configure(netdev, false);

	/* Step 3: Free resources
	 */
	nfp_net_close_free_all(nn);

	nn_dbg(nn, "%s down", netdev->name);
	return 0;
}