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
 int BCM_ENETSW_STATS_LEN ; 
 int EINVAL ; 
#define  ETH_SS_STATS 128 

__attribute__((used)) static int bcm_enetsw_get_sset_count(struct net_device *netdev,
				     int string_set)
{
	switch (string_set) {
	case ETH_SS_STATS:
		return BCM_ENETSW_STATS_LEN;
	default:
		return -EINVAL;
	}
}