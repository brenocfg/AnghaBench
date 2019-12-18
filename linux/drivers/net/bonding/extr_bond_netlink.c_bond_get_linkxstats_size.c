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
#define  IFLA_STATS_LINK_XSTATS 129 
#define  IFLA_STATS_LINK_XSTATS_SLAVE 128 
 size_t bond_3ad_stats_size () ; 
 size_t nla_total_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t bond_get_linkxstats_size(const struct net_device *dev, int attr)
{
	switch (attr) {
	case IFLA_STATS_LINK_XSTATS:
	case IFLA_STATS_LINK_XSTATS_SLAVE:
		break;
	default:
		return 0;
	}

	return bond_3ad_stats_size() + nla_total_size(0);
}