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

/* Variables and functions */
#define  PHY_LINK_SPEED_100MBPS 135 
#define  PHY_LINK_SPEED_10GBPS 134 
#define  PHY_LINK_SPEED_10MBPS 133 
#define  PHY_LINK_SPEED_1GBPS 132 
#define  PHY_LINK_SPEED_20GBPS 131 
#define  PHY_LINK_SPEED_25GBPS 130 
#define  PHY_LINK_SPEED_40GBPS 129 
#define  PHY_LINK_SPEED_ZERO 128 

__attribute__((used)) static int be_mac_to_link_speed(int mac_speed)
{
	switch (mac_speed) {
	case PHY_LINK_SPEED_ZERO:
		return 0;
	case PHY_LINK_SPEED_10MBPS:
		return 10;
	case PHY_LINK_SPEED_100MBPS:
		return 100;
	case PHY_LINK_SPEED_1GBPS:
		return 1000;
	case PHY_LINK_SPEED_10GBPS:
		return 10000;
	case PHY_LINK_SPEED_20GBPS:
		return 20000;
	case PHY_LINK_SPEED_25GBPS:
		return 25000;
	case PHY_LINK_SPEED_40GBPS:
		return 40000;
	}
	return 0;
}