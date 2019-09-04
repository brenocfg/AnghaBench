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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int dcbx_cap; } ;

/* Variables and functions */
#define  DCB_CAP_ATTR_BCN 135 
#define  DCB_CAP_ATTR_DCBX 134 
#define  DCB_CAP_ATTR_GSP 133 
#define  DCB_CAP_ATTR_PFC 132 
#define  DCB_CAP_ATTR_PFC_TCS 131 
#define  DCB_CAP_ATTR_PG 130 
#define  DCB_CAP_ATTR_PG_TCS 129 
#define  DCB_CAP_ATTR_UP2TC 128 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 ixgbe_dcbnl_getcap(struct net_device *netdev, int capid, u8 *cap)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	switch (capid) {
	case DCB_CAP_ATTR_PG:
		*cap = true;
		break;
	case DCB_CAP_ATTR_PFC:
		*cap = true;
		break;
	case DCB_CAP_ATTR_UP2TC:
		*cap = false;
		break;
	case DCB_CAP_ATTR_PG_TCS:
		*cap = 0x80;
		break;
	case DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;
		break;
	case DCB_CAP_ATTR_GSP:
		*cap = true;
		break;
	case DCB_CAP_ATTR_BCN:
		*cap = false;
		break;
	case DCB_CAP_ATTR_DCBX:
		*cap = adapter->dcbx_cap;
		break;
	default:
		*cap = false;
		break;
	}

	return 0;
}