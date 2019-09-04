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
struct TYPE_2__ {int num_vfs_alloced; } ;
struct octeon_device {TYPE_1__ sriov_info; } ;
struct oct_vf_stats {int /*<<< orphan*/  multicast; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ifla_vf_stats {int /*<<< orphan*/  multicast; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;

/* Variables and functions */
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int cn23xx_get_vf_stats (struct octeon_device*,int,struct oct_vf_stats*) ; 
 int /*<<< orphan*/  memset (struct oct_vf_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int liquidio_get_vf_stats(struct net_device *netdev, int vfidx,
				 struct ifla_vf_stats *vf_stats)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct oct_vf_stats stats;
	int ret;

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		return -EINVAL;

	memset(&stats, 0, sizeof(struct oct_vf_stats));
	ret = cn23xx_get_vf_stats(oct, vfidx, &stats);
	if (!ret) {
		vf_stats->rx_packets = stats.rx_packets;
		vf_stats->tx_packets = stats.tx_packets;
		vf_stats->rx_bytes = stats.rx_bytes;
		vf_stats->tx_bytes = stats.tx_bytes;
		vf_stats->broadcast = stats.broadcast;
		vf_stats->multicast = stats.multicast;
	}

	return ret;
}