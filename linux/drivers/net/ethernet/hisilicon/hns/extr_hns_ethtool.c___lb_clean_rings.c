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
struct TYPE_2__ {unsigned long rx_packets; unsigned long rx_bytes; unsigned long rx_frame_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct hns_nic_ring_data {int /*<<< orphan*/  (* poll_one ) (struct hns_nic_ring_data*,int,int /*<<< orphan*/ ) ;} ;
struct hns_nic_priv {struct hns_nic_ring_data* ring_data; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lb_other_process ; 
 int /*<<< orphan*/  stub1 (struct hns_nic_ring_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __lb_clean_rings(struct hns_nic_priv *priv,
			    int ringid0, int ringid1, int budget)
{
	int i, ret;
	struct hns_nic_ring_data *ring_data;
	struct net_device *ndev = priv->netdev;
	unsigned long rx_packets = ndev->stats.rx_packets;
	unsigned long rx_bytes = ndev->stats.rx_bytes;
	unsigned long rx_frame_errors = ndev->stats.rx_frame_errors;

	for (i = ringid0; i <= ringid1; i++) {
		ring_data = &priv->ring_data[i];
		(void)ring_data->poll_one(ring_data,
					  budget, __lb_other_process);
	}
	ret = (int)(ndev->stats.rx_packets - rx_packets);
	ndev->stats.rx_packets = rx_packets;
	ndev->stats.rx_bytes = rx_bytes;
	ndev->stats.rx_frame_errors = rx_frame_errors;
	return ret;
}