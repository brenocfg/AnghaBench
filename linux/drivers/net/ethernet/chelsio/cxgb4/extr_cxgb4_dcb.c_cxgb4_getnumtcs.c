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
struct TYPE_2__ {int msgs; int pg_num_tcs_supported; } ;
struct port_info {TYPE_1__ dcb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CXGB4_DCB_FW_PGRATE ; 
#define  DCB_NUMTCS_ATTR_PFC 129 
#define  DCB_NUMTCS_ATTR_PG 128 
 int EINVAL ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static int cxgb4_getnumtcs(struct net_device *dev, int tcs_id, u8 *num)
{
	struct port_info *pi = netdev2pinfo(dev);

	switch (tcs_id) {
	case DCB_NUMTCS_ATTR_PG:
		if (pi->dcb.msgs & CXGB4_DCB_FW_PGRATE)
			*num = pi->dcb.pg_num_tcs_supported;
		else
			*num = 0x8;
		break;

	case DCB_NUMTCS_ATTR_PFC:
		*num = 0x8;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}