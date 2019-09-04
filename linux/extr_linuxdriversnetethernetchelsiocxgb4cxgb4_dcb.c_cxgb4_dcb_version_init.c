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
struct port_dcb_info {int /*<<< orphan*/  dcb_version; } ;
struct port_info {struct port_dcb_info dcb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PORT_DCB_VER_AUTO ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

void cxgb4_dcb_version_init(struct net_device *dev)
{
	struct port_info *pi = netdev2pinfo(dev);
	struct port_dcb_info *dcb = &pi->dcb;

	/* Any writes here are only done on kernels that exlicitly need
	 * a specific version, say < 2.6.38 which only support CEE
	 */
	dcb->dcb_version = FW_PORT_DCB_VER_AUTO;
}