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
typedef  int u32 ;
struct TYPE_2__ {int alg; } ;
struct xenvif {TYPE_1__ hash; } ;

/* Variables and functions */
#define  XEN_NETIF_CTRL_HASH_ALGORITHM_NONE 129 
#define  XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ 128 
 int XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER ; 
 int XEN_NETIF_CTRL_STATUS_SUCCESS ; 

u32 xenvif_set_hash_alg(struct xenvif *vif, u32 alg)
{
	switch (alg) {
	case XEN_NETIF_CTRL_HASH_ALGORITHM_NONE:
	case XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ:
		break;

	default:
		return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;
	}

	vif->hash.alg = alg;

	return XEN_NETIF_CTRL_STATUS_SUCCESS;
}