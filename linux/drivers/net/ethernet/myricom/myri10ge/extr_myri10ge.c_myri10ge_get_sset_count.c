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
struct myri10ge_priv {int num_slices; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int MYRI10GE_MAIN_STATS_LEN ; 
 int MYRI10GE_SLICE_STATS_LEN ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int myri10ge_get_sset_count(struct net_device *netdev, int sset)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	switch (sset) {
	case ETH_SS_STATS:
		return MYRI10GE_MAIN_STATS_LEN +
		    mgp->num_slices * MYRI10GE_SLICE_STATS_LEN;
	default:
		return -EOPNOTSUPP;
	}
}