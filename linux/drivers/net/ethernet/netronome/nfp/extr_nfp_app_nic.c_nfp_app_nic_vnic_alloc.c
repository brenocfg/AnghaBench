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
struct nfp_net {int /*<<< orphan*/  port; TYPE_1__ dp; } ;
struct nfp_app {int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 int nfp_app_nic_vnic_init_phy_port (int /*<<< orphan*/ ,struct nfp_app*,struct nfp_net*,unsigned int) ; 
 int /*<<< orphan*/  nfp_net_get_mac_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfp_app_nic_vnic_alloc(struct nfp_app *app, struct nfp_net *nn,
			   unsigned int id)
{
	int err;

	err = nfp_app_nic_vnic_init_phy_port(app->pf, app, nn, id);
	if (err)
		return err < 0 ? err : 0;

	nfp_net_get_mac_addr(app->pf, nn->dp.netdev, nn->port);

	return 0;
}