#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nfp_pf {int /*<<< orphan*/  eth_tbl; } ;
struct TYPE_7__ {int /*<<< orphan*/  netdev; } ;
struct nfp_net {TYPE_2__* port; TYPE_1__ dp; } ;
struct nfp_app {int dummy; } ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 scalar_t__ NFP_PORT_INVALID ; 
 int /*<<< orphan*/  NFP_PORT_PHYS_PORT ; 
 int PTR_ERR (TYPE_2__*) ; 
 TYPE_2__* nfp_port_alloc (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_port_free (TYPE_2__*) ; 
 int nfp_port_init_phy_port (struct nfp_pf*,struct nfp_app*,TYPE_2__*,unsigned int) ; 

int nfp_app_nic_vnic_init_phy_port(struct nfp_pf *pf, struct nfp_app *app,
				   struct nfp_net *nn, unsigned int id)
{
	int err;

	if (!pf->eth_tbl)
		return 0;

	nn->port = nfp_port_alloc(app, NFP_PORT_PHYS_PORT, nn->dp.netdev);
	if (IS_ERR(nn->port))
		return PTR_ERR(nn->port);

	err = nfp_port_init_phy_port(pf, app, nn->port, id);
	if (err) {
		nfp_port_free(nn->port);
		return err;
	}

	return nn->port->type == NFP_PORT_INVALID;
}