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
struct TYPE_2__ {int ctrl; } ;
struct nfp_net {int /*<<< orphan*/ * vxlan_ports; TYPE_1__ dp; } ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NFP_NET_CFG_CTRL_VXLAN ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_VXLAN ; 
 scalar_t__ NFP_NET_CFG_VXLAN_PORT ; 
 int NFP_NET_N_VXLAN_PORTS ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_reconfig_post (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,scalar_t__,int) ; 

__attribute__((used)) static void nfp_net_set_vxlan_port(struct nfp_net *nn, int idx, __be16 port)
{
	int i;

	nn->vxlan_ports[idx] = port;

	if (!(nn->dp.ctrl & NFP_NET_CFG_CTRL_VXLAN))
		return;

	BUILD_BUG_ON(NFP_NET_N_VXLAN_PORTS & 1);
	for (i = 0; i < NFP_NET_N_VXLAN_PORTS; i += 2)
		nn_writel(nn, NFP_NET_CFG_VXLAN_PORT + i * sizeof(port),
			  be16_to_cpu(nn->vxlan_ports[i + 1]) << 16 |
			  be16_to_cpu(nn->vxlan_ports[i]));

	nfp_net_reconfig_post(nn, NFP_NET_CFG_UPDATE_VXLAN);
}