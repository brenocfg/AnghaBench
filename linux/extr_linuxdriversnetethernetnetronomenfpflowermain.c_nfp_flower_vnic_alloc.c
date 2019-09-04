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
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;
struct nfp_net {int vnic_no_name; int /*<<< orphan*/  port; TYPE_1__ dp; } ;
struct nfp_app {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_PORT_INVALID ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_keep_dst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_port_alloc (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nfp_flower_vnic_alloc(struct nfp_app *app, struct nfp_net *nn,
				 unsigned int id)
{
	if (id > 0) {
		nfp_warn(app->cpp, "FlowerNIC doesn't support more than one data vNIC\n");
		goto err_invalid_port;
	}

	eth_hw_addr_random(nn->dp.netdev);
	netif_keep_dst(nn->dp.netdev);
	nn->vnic_no_name = true;

	return 0;

err_invalid_port:
	nn->port = nfp_port_alloc(app, NFP_PORT_INVALID, nn->dp.netdev);
	return PTR_ERR_OR_ZERO(nn->port);
}