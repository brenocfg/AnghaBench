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
typedef  int u32 ;
struct aggregator {int /*<<< orphan*/  lag_ports; } ;

/* Variables and functions */
#define  AD_LINK_SPEED_100000MBPS 141 
#define  AD_LINK_SPEED_10000MBPS 140 
#define  AD_LINK_SPEED_1000MBPS 139 
#define  AD_LINK_SPEED_100MBPS 138 
#define  AD_LINK_SPEED_10MBPS 137 
#define  AD_LINK_SPEED_14000MBPS 136 
#define  AD_LINK_SPEED_1MBPS 135 
#define  AD_LINK_SPEED_20000MBPS 134 
#define  AD_LINK_SPEED_25000MBPS 133 
#define  AD_LINK_SPEED_2500MBPS 132 
#define  AD_LINK_SPEED_40000MBPS 131 
#define  AD_LINK_SPEED_50000MBPS 130 
#define  AD_LINK_SPEED_5000MBPS 129 
#define  AD_LINK_SPEED_56000MBPS 128 
 int __agg_active_ports (struct aggregator*) ; 
 int __get_link_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 __get_agg_bandwidth(struct aggregator *aggregator)
{
	int nports = __agg_active_ports(aggregator);
	u32 bandwidth = 0;

	if (nports) {
		switch (__get_link_speed(aggregator->lag_ports)) {
		case AD_LINK_SPEED_1MBPS:
			bandwidth = nports;
			break;
		case AD_LINK_SPEED_10MBPS:
			bandwidth = nports * 10;
			break;
		case AD_LINK_SPEED_100MBPS:
			bandwidth = nports * 100;
			break;
		case AD_LINK_SPEED_1000MBPS:
			bandwidth = nports * 1000;
			break;
		case AD_LINK_SPEED_2500MBPS:
			bandwidth = nports * 2500;
			break;
		case AD_LINK_SPEED_5000MBPS:
			bandwidth = nports * 5000;
			break;
		case AD_LINK_SPEED_10000MBPS:
			bandwidth = nports * 10000;
			break;
		case AD_LINK_SPEED_14000MBPS:
			bandwidth = nports * 14000;
			break;
		case AD_LINK_SPEED_20000MBPS:
			bandwidth = nports * 20000;
			break;
		case AD_LINK_SPEED_25000MBPS:
			bandwidth = nports * 25000;
			break;
		case AD_LINK_SPEED_40000MBPS:
			bandwidth = nports * 40000;
			break;
		case AD_LINK_SPEED_50000MBPS:
			bandwidth = nports * 50000;
			break;
		case AD_LINK_SPEED_56000MBPS:
			bandwidth = nports * 56000;
			break;
		case AD_LINK_SPEED_100000MBPS:
			bandwidth = nports * 100000;
			break;
		default:
			bandwidth = 0; /* to silence the compiler */
		}
	}
	return bandwidth;
}