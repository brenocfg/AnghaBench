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
struct cpsw_common {int rx_ch_num; int tx_ch_num; } ;

/* Variables and functions */
 int CPSW_STATS_CH_LEN ; 
 int CPSW_STATS_COMMON_LEN ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 

int cpsw_get_sset_count(struct net_device *ndev, int sset)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	switch (sset) {
	case ETH_SS_STATS:
		return (CPSW_STATS_COMMON_LEN +
		       (cpsw->rx_ch_num + cpsw->tx_ch_num) *
		       CPSW_STATS_CH_LEN);
	default:
		return -EOPNOTSUPP;
	}
}