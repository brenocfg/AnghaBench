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
struct nfp_port {int eth_id; scalar_t__ eth_stats; TYPE_1__* eth_port; int /*<<< orphan*/  type; } ;
struct nfp_pf {scalar_t__ mac_stats_mem; TYPE_2__* eth_tbl; } ;
struct nfp_app {int /*<<< orphan*/  cpp; } ;
struct TYPE_4__ {unsigned int count; TYPE_1__* ports; } ;
struct TYPE_3__ {int index; scalar_t__ override_changed; } ;

/* Variables and functions */
 int EINVAL ; 
 int NFP_MAC_STATS_SIZE ; 
 int /*<<< orphan*/  NFP_PORT_INVALID ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,int) ; 

int nfp_port_init_phy_port(struct nfp_pf *pf, struct nfp_app *app,
			   struct nfp_port *port, unsigned int id)
{
	/* Check if vNIC has external port associated and cfg is OK */
	if (!pf->eth_tbl || id >= pf->eth_tbl->count) {
		nfp_err(app->cpp,
			"NSP port entries don't match vNICs (no entry %d)\n",
			id);
		return -EINVAL;
	}
	if (pf->eth_tbl->ports[id].override_changed) {
		nfp_warn(app->cpp,
			 "Config changed for port #%d, reboot required before port will be operational\n",
			 pf->eth_tbl->ports[id].index);
		port->type = NFP_PORT_INVALID;
		return 0;
	}

	port->eth_port = &pf->eth_tbl->ports[id];
	port->eth_id = pf->eth_tbl->ports[id].index;
	if (pf->mac_stats_mem)
		port->eth_stats =
			pf->mac_stats_mem + port->eth_id * NFP_MAC_STATS_SIZE;

	return 0;
}