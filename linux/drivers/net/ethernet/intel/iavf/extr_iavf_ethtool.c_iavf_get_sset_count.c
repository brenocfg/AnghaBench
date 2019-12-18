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

/* Variables and functions */
 int EINVAL ; 
 int ETH_SS_PRIV_FLAGS ; 
 int ETH_SS_STATS ; 
 int IAVF_MAX_REQ_QUEUES ; 
 int IAVF_PRIV_FLAGS_STR_LEN ; 
 int IAVF_QUEUE_STATS_LEN ; 
 int IAVF_STATS_LEN ; 

__attribute__((used)) static int iavf_get_sset_count(struct net_device *netdev, int sset)
{
	if (sset == ETH_SS_STATS)
		return IAVF_STATS_LEN +
			(IAVF_QUEUE_STATS_LEN * 2 * IAVF_MAX_REQ_QUEUES);
	else if (sset == ETH_SS_PRIV_FLAGS)
		return IAVF_PRIV_FLAGS_STR_LEN;
	else
		return -EINVAL;
}