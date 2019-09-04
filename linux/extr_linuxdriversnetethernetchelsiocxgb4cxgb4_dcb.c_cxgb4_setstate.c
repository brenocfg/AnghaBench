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
struct TYPE_2__ {scalar_t__ state; int enabled; } ;
struct port_info {TYPE_1__ dcb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CXGB4_DCB_STATE_FW_ALLSYNCED ; 
 scalar_t__ CXGB4_DCB_STATE_HOST ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static u8 cxgb4_setstate(struct net_device *dev, u8 enabled)
{
	struct port_info *pi = netdev2pinfo(dev);

	/* If DCBx is host-managed, dcb is enabled by outside lldp agents */
	if (pi->dcb.state == CXGB4_DCB_STATE_HOST) {
		pi->dcb.enabled = enabled;
		return 0;
	}

	/* Firmware doesn't provide any mechanism to control the DCB state.
	 */
	if (enabled != (pi->dcb.state == CXGB4_DCB_STATE_FW_ALLSYNCED))
		return 1;

	return 0;
}