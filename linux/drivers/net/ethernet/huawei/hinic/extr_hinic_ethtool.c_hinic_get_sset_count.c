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
struct hinic_dev {int num_qps; } ;

/* Variables and functions */
 int ARRAY_LEN (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/  hinic_function_stats ; 
 int /*<<< orphan*/  hinic_port_stats ; 
 int /*<<< orphan*/  hinic_rx_queue_stats ; 
 int /*<<< orphan*/  hinic_tx_queue_stats ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hinic_get_sset_count(struct net_device *netdev, int sset)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	int count, q_num;

	switch (sset) {
	case ETH_SS_STATS:
		q_num = nic_dev->num_qps;
		count = ARRAY_LEN(hinic_function_stats) +
			(ARRAY_LEN(hinic_tx_queue_stats) +
			ARRAY_LEN(hinic_rx_queue_stats)) * q_num;

		count += ARRAY_LEN(hinic_port_stats);

		return count;
	default:
		return -EOPNOTSUPP;
	}
}