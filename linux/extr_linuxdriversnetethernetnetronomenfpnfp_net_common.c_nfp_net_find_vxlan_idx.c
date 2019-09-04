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
struct nfp_net {scalar_t__* vxlan_ports; int /*<<< orphan*/ * vxlan_usecnt; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int ENOSPC ; 
 int NFP_NET_N_VXLAN_PORTS ; 

__attribute__((used)) static int nfp_net_find_vxlan_idx(struct nfp_net *nn, __be16 port)
{
	int i, free_idx = -ENOSPC;

	for (i = 0; i < NFP_NET_N_VXLAN_PORTS; i++) {
		if (nn->vxlan_ports[i] == port)
			return i;
		if (!nn->vxlan_usecnt[i])
			free_idx = i;
	}

	return free_idx;
}