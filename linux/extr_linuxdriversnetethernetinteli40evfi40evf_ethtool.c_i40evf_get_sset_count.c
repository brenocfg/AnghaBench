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
 int I40EVF_PRIV_FLAGS_STR_LEN ; 
 int I40EVF_STATS_LEN (struct net_device*) ; 

__attribute__((used)) static int i40evf_get_sset_count(struct net_device *netdev, int sset)
{
	if (sset == ETH_SS_STATS)
		return I40EVF_STATS_LEN(netdev);
	else if (sset == ETH_SS_PRIV_FLAGS)
		return I40EVF_PRIV_FLAGS_STR_LEN;
	else
		return -EINVAL;
}