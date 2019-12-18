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
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 
 int NB8800_NUM_STATS ; 

__attribute__((used)) static int nb8800_get_sset_count(struct net_device *dev, int sset)
{
	if (sset == ETH_SS_STATS)
		return NB8800_NUM_STATS;

	return -EOPNOTSUPP;
}