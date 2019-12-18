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
 int ETH_SS_STATS ; 
 int GMAC_STATS_NUM ; 

__attribute__((used)) static int gmac_get_sset_count(struct net_device *netdev, int sset)
{
	return sset == ETH_SS_STATS ? GMAC_STATS_NUM : 0;
}