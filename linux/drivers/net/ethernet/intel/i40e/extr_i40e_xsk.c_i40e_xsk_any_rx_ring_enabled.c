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
struct net_device {int dummy; } ;
struct i40e_vsi {int num_queue_pairs; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ xdp_get_umem_from_qid (struct net_device*,int) ; 

bool i40e_xsk_any_rx_ring_enabled(struct i40e_vsi *vsi)
{
	struct net_device *netdev = vsi->netdev;
	int i;

	for (i = 0; i < vsi->num_queue_pairs; i++) {
		if (xdp_get_umem_from_qid(netdev, i))
			return true;
	}

	return false;
}