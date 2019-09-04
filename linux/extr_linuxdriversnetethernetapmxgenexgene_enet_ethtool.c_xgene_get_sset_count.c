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
 int ETH_SS_STATS ; 
 int XGENE_EXTD_STATS_LEN ; 
 int XGENE_STATS_LEN ; 

__attribute__((used)) static int xgene_get_sset_count(struct net_device *ndev, int sset)
{
	if (sset != ETH_SS_STATS)
		return -EINVAL;

	return XGENE_STATS_LEN + XGENE_EXTD_STATS_LEN;
}