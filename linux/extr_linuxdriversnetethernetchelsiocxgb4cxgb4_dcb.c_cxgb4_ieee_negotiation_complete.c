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
struct port_dcb_info {scalar_t__ state; int msgs; int supported; } ;
struct port_info {struct port_dcb_info dcb; } ;
struct net_device {int dummy; } ;
typedef  enum cxgb4_dcb_fw_msgs { ____Placeholder_cxgb4_dcb_fw_msgs } cxgb4_dcb_fw_msgs ;

/* Variables and functions */
 scalar_t__ CXGB4_DCB_STATE_FW_ALLSYNCED ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 scalar_t__ cxgb4_dcb_state_synced (scalar_t__) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static inline int
cxgb4_ieee_negotiation_complete(struct net_device *dev,
				enum cxgb4_dcb_fw_msgs dcb_subtype)
{
	struct port_info *pi = netdev2pinfo(dev);
	struct port_dcb_info *dcb = &pi->dcb;

	if (dcb->state == CXGB4_DCB_STATE_FW_ALLSYNCED)
		if (dcb_subtype && !(dcb->msgs & dcb_subtype))
			return 0;

	return (cxgb4_dcb_state_synced(dcb->state) &&
		(dcb->supported & DCB_CAP_DCBX_VER_IEEE));
}