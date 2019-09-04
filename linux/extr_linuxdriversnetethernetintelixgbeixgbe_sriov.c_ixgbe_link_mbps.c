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
struct ixgbe_adapter {int link_speed; } ;

/* Variables and functions */
#define  IXGBE_LINK_SPEED_100_FULL 130 
#define  IXGBE_LINK_SPEED_10GB_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 

int ixgbe_link_mbps(struct ixgbe_adapter *adapter)
{
	switch (adapter->link_speed) {
	case IXGBE_LINK_SPEED_100_FULL:
		return 100;
	case IXGBE_LINK_SPEED_1GB_FULL:
		return 1000;
	case IXGBE_LINK_SPEED_10GB_FULL:
		return 10000;
	default:
		return 0;
	}
}