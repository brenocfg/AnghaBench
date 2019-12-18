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
struct vxgedev {int no_of_vpath; int max_config_port; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int DRIVER_STAT_LEN ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int VXGE_HW_AGGR_STATS_LEN ; 
 int VXGE_HW_PORT_STATS_LEN ; 
 int VXGE_HW_VPATH_RX_STATS_LEN ; 
 int VXGE_HW_VPATH_STATS_LEN ; 
 int VXGE_HW_VPATH_TX_STATS_LEN ; 
 int VXGE_SW_STATS_LEN ; 
 int VXGE_TITLE_LEN ; 
 struct vxgedev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int vxge_ethtool_get_sset_count(struct net_device *dev, int sset)
{
	struct vxgedev *vdev = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return VXGE_TITLE_LEN +
			(vdev->no_of_vpath * VXGE_HW_VPATH_STATS_LEN) +
			(vdev->max_config_port * VXGE_HW_AGGR_STATS_LEN) +
			(vdev->max_config_port * VXGE_HW_PORT_STATS_LEN) +
			(vdev->no_of_vpath * VXGE_HW_VPATH_TX_STATS_LEN) +
			(vdev->no_of_vpath * VXGE_HW_VPATH_RX_STATS_LEN) +
			(vdev->no_of_vpath * VXGE_SW_STATS_LEN) +
			DRIVER_STAT_LEN;
	default:
		return -EOPNOTSUPP;
	}
}