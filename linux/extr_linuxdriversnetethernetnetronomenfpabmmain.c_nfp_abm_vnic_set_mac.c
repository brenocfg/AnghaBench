#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nfp_pf {int /*<<< orphan*/  cpp; int /*<<< orphan*/  hwinfo; TYPE_1__* eth_tbl; } ;
struct TYPE_5__ {TYPE_3__* netdev; } ;
struct nfp_net {TYPE_2__ dp; } ;
struct nfp_eth_table_port {int eth_index; } ;
struct nfp_abm {int pf_id; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_6__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {unsigned int count; struct nfp_eth_table_port* ports; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_3__*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* nfp_hwinfo_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfp_abm_vnic_set_mac(struct nfp_pf *pf, struct nfp_abm *abm, struct nfp_net *nn,
		     unsigned int id)
{
	struct nfp_eth_table_port *eth_port = &pf->eth_tbl->ports[id];
	u8 mac_addr[ETH_ALEN];
	const char *mac_str;
	char name[32];

	if (id > pf->eth_tbl->count) {
		nfp_warn(pf->cpp, "No entry for persistent MAC address\n");
		eth_hw_addr_random(nn->dp.netdev);
		return;
	}

	snprintf(name, sizeof(name), "eth%u.mac.pf%u",
		 eth_port->eth_index, abm->pf_id);

	mac_str = nfp_hwinfo_lookup(pf->hwinfo, name);
	if (!mac_str) {
		nfp_warn(pf->cpp, "Can't lookup persistent MAC address (%s)\n",
			 name);
		eth_hw_addr_random(nn->dp.netdev);
		return;
	}

	if (sscanf(mac_str, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		   &mac_addr[0], &mac_addr[1], &mac_addr[2],
		   &mac_addr[3], &mac_addr[4], &mac_addr[5]) != 6) {
		nfp_warn(pf->cpp, "Can't parse persistent MAC address (%s)\n",
			 mac_str);
		eth_hw_addr_random(nn->dp.netdev);
		return;
	}

	ether_addr_copy(nn->dp.netdev->dev_addr, mac_addr);
	ether_addr_copy(nn->dp.netdev->perm_addr, mac_addr);
}