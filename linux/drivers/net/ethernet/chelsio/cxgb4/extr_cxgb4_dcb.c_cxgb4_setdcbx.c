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
struct TYPE_2__ {int supported; int /*<<< orphan*/  state; } ;
struct port_info {TYPE_1__ dcb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CXGB4_DCBX_FW_SUPPORT ; 
 int CXGB4_DCBX_HOST_SUPPORT ; 
 int /*<<< orphan*/  cxgb4_dcb_state_synced (int /*<<< orphan*/ ) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static u8 cxgb4_setdcbx(struct net_device *dev, u8 dcb_request)
{
	struct port_info *pi = netdev2pinfo(dev);

	/* Filter out requests which exceed our capabilities.
	 */
	if ((dcb_request & (CXGB4_DCBX_FW_SUPPORT | CXGB4_DCBX_HOST_SUPPORT))
	    != dcb_request)
		return 1;

	/* Can't enable DCB if we haven't successfully negotiated it.
	 */
	if (!cxgb4_dcb_state_synced(pi->dcb.state))
		return 1;

	/* There's currently no mechanism to allow for the firmware DCBX
	 * negotiation to be changed from the Host Driver.  If the caller
	 * requests exactly the same parameters that we already have then
	 * we'll allow them to be successfully "set" ...
	 */
	if (dcb_request != pi->dcb.supported)
		return 1;

	pi->dcb.supported = dcb_request;
	return 0;
}