#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int supported; } ;
struct port_info {TYPE_1__ dcb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  DCB_CAP_ATTR_BCN 135 
#define  DCB_CAP_ATTR_DCBX 134 
#define  DCB_CAP_ATTR_GSP 133 
#define  DCB_CAP_ATTR_PFC 132 
#define  DCB_CAP_ATTR_PFC_TCS 131 
#define  DCB_CAP_ATTR_PG 130 
#define  DCB_CAP_ATTR_PG_TCS 129 
#define  DCB_CAP_ATTR_UP2TC 128 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static u8 cxgb4_getcap(struct net_device *dev, int cap_id, u8 *caps)
{
	struct port_info *pi = netdev2pinfo(dev);

	switch (cap_id) {
	case DCB_CAP_ATTR_PG:
	case DCB_CAP_ATTR_PFC:
		*caps = true;
		break;

	case DCB_CAP_ATTR_PG_TCS:
		/* 8 priorities for PG represented by bitmap */
		*caps = 0x80;
		break;

	case DCB_CAP_ATTR_PFC_TCS:
		/* 8 priorities for PFC represented by bitmap */
		*caps = 0x80;
		break;

	case DCB_CAP_ATTR_GSP:
		*caps = true;
		break;

	case DCB_CAP_ATTR_UP2TC:
	case DCB_CAP_ATTR_BCN:
		*caps = false;
		break;

	case DCB_CAP_ATTR_DCBX:
		*caps = pi->dcb.supported;
		break;

	default:
		*caps = false;
	}

	return 0;
}