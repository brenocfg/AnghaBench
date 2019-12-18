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
 scalar_t__ ATH6KL_STATS_LEN ; 
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 

__attribute__((used)) static int ath6kl_get_sset_count(struct net_device *dev, int sset)
{
	int rv = 0;

	if (sset == ETH_SS_STATS)
		rv += ATH6KL_STATS_LEN;

	if (rv == 0)
		return -EOPNOTSUPP;
	return rv;
}